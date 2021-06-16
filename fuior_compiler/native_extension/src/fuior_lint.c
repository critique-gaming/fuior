#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <tree_sitter/api.h>

#include "fuior.h"
#include "fuior_private.h"
#include "fuior_strlist.h"
#include "fuior_list.h"

const char * const special_commands_lint[] = {
    #define CMD_ENUM 0
    "enum",
    #define CMD_DECLARE_CMD 1
    "declare_cmd",
    NULL
};

static TSNode next_node(TSSymbol symbol, TSNode node) {
    while (1) {
        if (ts_node_is_null(node)) { break; }
        node = ts_node_next_named_sibling(node);
        if (ts_node_is_null(node)) { break; }
        if (ts_node_symbol(node) == symbol) { break; }
    }
    return node;
}

fuior_command *fuior_command_register(fuior_state *state, const char *name) {
    fuior_command *cmd = (fuior_command*)calloc(1, sizeof(fuior_command));
    fuior_map_set(&state->commands, name, cmd);
    return cmd;
}

fuior_type *type_from_name(fuior_state *state, const char *type_name) {
    // TODO: Handle more complicated strings like A|B or optionals
    if (type_name[0] == '?') {
      fuior_type *root_type = type_from_name(state, type_name + 1);
      if (!root_type) return NULL;
      fuior_type* t = fuior_type_new(state, TYPE_UNION);
      fuior_list_push(&t->as_op.items, root_type);
      fuior_list_push(&t->as_op.items, state->type_nil);
      return t;
    }
    return (fuior_type*)fuior_map_get(&state->named_types, type_name);
}

fuior_type *type_from_node(fuior_state *state, TSNode node) {
    if (ts_node_is_null(node)) {
        add_error(node, "Invalid type expression");
        return NULL;
    }

    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.type_identifier) {
        char *type_name = fuior_node_to_string(state, node);
        fuior_type * type = (fuior_type*)fuior_map_get(&state->named_types, type_name);
        if (!type) { add_error(node, "Undefined type \"%s\"", type_name); }
        free(type_name);
        return type;
    }

    if (symbol == sym.unary_type_expression) {
        TSNode op_node = ts_node_child(node, 0);
        TSNode expr_node = ts_node_child(node, 1);
        if (ts_node_is_null(op_node)) {
            add_error(node, "Invalid unary type expression");
            return NULL;
        }
        fuior_type * t = NULL;
        char * op = fuior_node_to_string(state, op_node);
        if (0 == strcmp(op, "?")) {
            fuior_type *child_type = type_from_node(state, expr_node);
            if (child_type) {
                t = fuior_type_new(state, TYPE_UNION);
                fuior_list_push(&t->as_op.items, child_type);
                fuior_list_push(&t->as_op.items, state->type_nil);
            }
        } else {
            add_error(op_node, "Unknown unary type operator \"%s\"", op);
        }
        free(op);
        return t;
    }

    // TODO: binary expressions and string literals

    add_error(node, "Unimplemented type expression");
    return NULL;
}

static fuior_type *type_from_container(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }
    return type_from_node(state, child);
}

static void handle_command(fuior_state *state, TSNode node) {
    int cmd = fuior_get_special_command(state, node, special_commands_lint);
    switch (cmd) {
        case -1: break;

        case CMD_ENUM: {
            TSNode arg1 = next_node(sym.command_arg, node);
            char * enum_name = fuior_command_arg_to_string(state, arg1);
            TSNode arg2 = next_node(sym.command_arg, arg1);
            char * item_name = fuior_command_arg_to_string(state, arg2);
            if (enum_name && item_name) {
                fuior_type *enum_type = (fuior_type*)fuior_map_get(&state->named_types, enum_name);
                if (!enum_type) {
                    enum_type = fuior_type_new(state, TYPE_ENUM);
                    enum_type->name = fuior_clone_string(enum_name);
                    fuior_map_set(&state->named_types, enum_name, (void*)enum_type);
                }
                if (enum_type->tag != TYPE_ENUM) {
                    add_error(arg1, "%s is not an enum type", enum_name);
                } else {
                    fuior_map_set(&enum_type->as_enum.items, item_name, (void*)1);
                }
            } else {
                add_error(node, "enum expects an enum name and an item");
            }
            free(enum_name);
            free(item_name);
            break;
        }

        case CMD_DECLARE_CMD: {
            TSNode arg1 = next_node(sym.command_arg, node);
            char * cmd_name = fuior_command_arg_to_string(state, arg1);
            if (!cmd_name) {
                add_error(node, "declare_cmd expects the command name");
                break;
            }

            fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, cmd_name);
            if (cmd) {
                add_error(arg1, "%s command already declared", cmd_name);
                free(cmd_name);
                break;
            }

            cmd = fuior_command_register(state, cmd_name);
            free(cmd_name);

            TSNode argname_node;
            TSNode argtype_node = arg1;
            while (true) {
                argname_node = next_node(sym.command_arg, argtype_node);
                if (ts_node_is_null(argname_node)) break;
                argtype_node = next_node(sym.command_arg, argname_node);
                char * argname = fuior_command_arg_to_string(state, argname_node);
                char * argtype = fuior_command_arg_to_string(state, argtype_node);
                if (!argname) {
                    add_error(node, "expected argument name");
                }
                if (!argtype) {
                    add_error(node, "expected argument type");
                }
                if (argname && argtype) {
                    fuior_type *type = type_from_name(state, argtype);
                    if (type) {
                        fuior_command_arg *arg = fuior_command_arg_new(argname, type);
                        bool add_to_list = true;
                        if (0 == strcmp("...", argname)) {
                            if (cmd->vararg) {
                                add_error(argname_node, "cannot use ... twice in the same command");
                            } else {
                                add_to_list = false;
                                cmd->vararg = arg;
                            }
                        }
                        if (add_to_list) {
                            fuior_list_push(&cmd->args, (void*)arg);
                        }
                    } else {
                        add_error(argtype_node, "unknown type %s", argtype);
                    }
                }
                free(argname);
                free(argtype);
            }

            break;
        }
    }
}

static fuior_type *type_of_node(fuior_state *state, TSNode node) {
    if (ts_node_is_null(node)) return state->type_any;

    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.boolean) return state->type_boolean;
    if (symbol == sym.number) return state->type_number;
    if (symbol == sym.intl_string) return state->type_string;

    if (symbol == sym.string) {
        fuior_type *typ = fuior_type_new(state, TYPE_STRING_LITERAL);
        typ->as_string_literal.literal = fuior_string_node_to_string(state, node);
        return typ;
    }

    if (symbol == sym.bare_word) {
        fuior_type *typ = fuior_type_new(state, TYPE_STRING_LITERAL);
        typ->as_string_literal.literal = fuior_node_to_string(state, node);
        return typ;
    }

    if (symbol == sym.paran_expression) {
        return type_of_node(state, fuior_skip_comments(ts_node_child(node, 0)));
    }

    if (symbol == sym.identifier) {
        char *varname = fuior_node_to_string(state, node);
        fuior_type * typ = (fuior_type*)fuior_map_get(&state->variables, varname);
        free(varname);
        return typ ? typ : state->type_any;
    }

    if (symbol == sym.unary_expression) {
        // TODO: handle expressions
        return state->type_any;
    }

    if (symbol == sym.binary_expression) {
        // TODO: handle expressions
        return state->type_any;
    }

    return state->type_any;
}

static bool can_cast_to(fuior_type *from, fuior_type *to) {
    if (from->tag == TYPE_ANY || to->tag == TYPE_ANY) return true;

    if (from->tag == TYPE_UNION) {
        for (fuior_list_item *it = from->as_op.items.first; it != NULL; it = it->next) {
            if (!can_cast_to((fuior_type*)it->data, to)) return false;
        }
        return true;
    }

    if (from->tag == TYPE_INTERSECTION) {
        for (fuior_list_item *it = from->as_op.items.first; it != NULL; it = it->next) {
            if (can_cast_to((fuior_type*)it->data, to)) return true;
        }
        return false;
    }

    if (to->tag == TYPE_UNION) {
        for (fuior_list_item *it = to->as_op.items.first; it != NULL; it = it->next) {
            if (can_cast_to(from, (fuior_type*)it->data)) return true;
        }
        return false;
    }

    if (to->tag == TYPE_INTERSECTION) {
        for (fuior_list_item *it = to->as_op.items.first; it != NULL; it = it->next) {
            if (!can_cast_to(to, (fuior_type*)it->data)) return false;
        }
        return true;
    }

    if (from->tag == TYPE_BOOLEAN) return to->tag == TYPE_BOOLEAN;
    if (from->tag == TYPE_NUMBER) return to->tag == TYPE_NUMBER;
    if (from->tag == TYPE_NIL) return to->tag == TYPE_NIL;
    if (from->tag == TYPE_STRING) return to->tag == TYPE_STRING;

    if (from->tag == TYPE_STRING_LITERAL) {
        if (to->tag == TYPE_STRING) return true;
        if (to->tag == TYPE_STRING_LITERAL) {
            return 0 == strcmp(from->as_string_literal.literal, to->as_string_literal.literal);
        }
        if (to->tag == TYPE_ENUM) {
            return fuior_map_get(&to->as_enum.items, from->as_string_literal.literal) != NULL;
        }
        return false;
    }

    return false;
}

static void check_animation(fuior_state *state, TSNode node, const char *actor, const char *animation) {
    char *name = (char*)malloc(sizeof(actor) + sizeof("animation_") + 1);
    strcpy(name, "animation_");
    strcat(name, actor);
    fuior_type *anim_enum = type_from_name(state, name);
    free(name);

    if (
        anim_enum == NULL ||
        anim_enum->tag != TYPE_ENUM ||
        fuior_map_get(&anim_enum->as_enum.items, animation) == NULL
    ) {
        add_error(node, "character \"%s\" doesn't have an animation named \"%s\"", actor, animation);
    }
}

static void typecheck_command(fuior_state *state, TSNode node) {
    char *verb = fuior_node_to_string(state, node);
    fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, verb);
    if (!cmd) {
        add_error(node, "unknown command %s", verb);
        free(verb);
        return;
    }

    TSNode parent = ts_node_parent(node);

    fuior_list_item *cmd_arg_it= cmd->args.first;
    int cmd_arg_count = 0;
    int arg_count = 0;

    bool is_animate = 0 == strcmp("animate", verb);
    char * animate_actor = NULL;

    for (
        TSNode it = ts_node_next_named_sibling(node);
        !ts_node_is_null(it);
        it = ts_node_next_named_sibling(it)
    ) {
        TSSymbol symbol = ts_node_symbol(it);
        if (symbol != sym.command_arg) continue;

        arg_count++;

        fuior_command_arg *argument = NULL;

        if (cmd_arg_it) {
            argument = (fuior_command_arg*)cmd_arg_it->data;
            cmd_arg_it = cmd_arg_it->next;
            cmd_arg_count++;
        } else {
            if (cmd->vararg) {
                argument = cmd->vararg;
            } else {
                add_error(it, "command %s only takes %d arguments", verb, cmd_arg_count);
            }
        }

        if (argument) {
            fuior_type *arg_type = type_of_node(state, fuior_skip_comments(ts_node_child(it, 0)));
            if (!can_cast_to(arg_type, argument->type)) {
                char *arg_type_name = fuior_type_name(arg_type);
                char *cmd_arg_type_name = fuior_type_name(argument->type);
                add_error(
                    it, "argument #%d(%s) of command %s is of wrong type: expected %s, got %s",
                    arg_count, argument->name, verb, cmd_arg_type_name, arg_type_name
                );
                free(arg_type_name);
                free(cmd_arg_type_name);
            }

            if (is_animate && arg_count == 1 && arg_type->tag == TYPE_STRING_LITERAL) {
                animate_actor = arg_type->as_string_literal.literal;
            }

            if (is_animate && arg_count == 2 && animate_actor && arg_type->tag == TYPE_STRING_LITERAL) {
                check_animation(state, it, animate_actor, arg_type->as_string_literal.literal);
            }
        }
    }

    while (cmd_arg_it) {
        fuior_command_arg *argument = (fuior_command_arg*)cmd_arg_it->data;
        cmd_arg_it = cmd_arg_it->next;
        cmd_arg_count++;

        if (!can_cast_to(state->type_nil, argument->type)) {
            add_error(parent, "argument #%d(%s) of command %s is not optional", cmd_arg_count, argument->name, verb);
        }
    }

    free(verb);
}

static void typecheck_assign_statement(fuior_state *state, TSNode node) {
    char *assign_name = NULL;
    char *assign_op = NULL;
    fuior_type *assign_type = NULL;

    for (
        TSNode it = ts_node_named_child(node, 0);
        !ts_node_is_null(it);
        it = ts_node_next_named_sibling(it)
    ) {
        TSSymbol symbol = ts_node_symbol(it);
        if (symbol == sym.comment) continue;

        if (symbol == sym.assign_lvalue) {
            assign_name = fuior_node_to_string(state, it);
            assign_type = (fuior_type*)fuior_map_get(&state->variables, assign_name);
            if (!assign_type) {
                add_error(it, "undeclared variable \"%s\"", assign_name);
                free(assign_name);
                assign_name = NULL;
            }
            continue;
        }

        if (!assign_name) continue;

        if (symbol == sym.assign_operator) {
            assign_op = fuior_node_to_string(state, it);
            if ((0 == strcmp("+", assign_op) || 0 == strcmp("-", assign_op)) && !can_cast_to(state->type_number, assign_type)) {
                char *type_name = fuior_type_name(assign_type);
                add_error(it, "cannot do a numeric operation on %s of type %s", assign_name, type_name);
                free(type_name);
            }

        } else if (symbol == sym.assign_rvalue) {
            fuior_type *rvalue_type = type_of_node(state, fuior_skip_comments(ts_node_child(it, 0)));
            if (!can_cast_to(rvalue_type, assign_type)) {
                char *assign_type_name = fuior_type_name(assign_type);
                char *rvalue_type_name = fuior_type_name(rvalue_type);
                add_error(it, "trying to assign value of incompatible type to %s: expected %s, got %s", assign_name, assign_type_name, rvalue_type_name);
                free(assign_type_name);
                free(rvalue_type_name);
            }
        }
    }

    free(assign_name);
    free(assign_op);
}

static void typecheck_text_statement(fuior_state *state, TSNode node) {
    char *actor = NULL;

    for (
        TSNode it = ts_node_named_child(node, 0);
        !ts_node_is_null(it);
        it = ts_node_next_named_sibling(it)
    ) {
        TSSymbol symbol = ts_node_symbol(it);
        if (symbol == sym.comment) continue;

        if (symbol == sym.text_actor) {
            actor = fuior_node_to_string(state, it);
            if (!fuior_map_get(&state->character_enum->as_enum.items, actor)) {
                add_error(it, "no such character \"%s\"", actor);
                free(actor);
                actor = NULL;
            }
        } else if (symbol == sym.text_animation && actor) {
            char *animation = fuior_node_to_string(state, it);
            check_animation(state, it, actor, animation);
            free(animation);
        }
    }

    free(actor);
}

static void collect_declare_var_statement(fuior_state *state, TSNode node) {
    TSNode name_node = ts_node_child_by_field_id(node, fld.name);
    if (ts_node_is_null(name_node)) return;

    TSNode type_node = ts_node_child_by_field_id(node, fld.type);
    fuior_type *var_type = NULL;
    if (!ts_node_is_null(type_node)) {
        var_type = type_from_container(state, type_node);
    }
    if (var_type == NULL) {
        var_type = state->type_any;
    }

    char *var_name = fuior_node_to_string(state, name_node);
    if (fuior_map_get(&state->variables, var_name)) {
        add_error(name_node, "variable %s already exists", var_name);
    }

    fuior_map_set(&state->variables, var_name, (void*)var_type);
    fuior_map_set(&state->varname_enum->as_enum.items, var_name, (void*)1);

    free(var_name);
}

static void scan_for_declarations(fuior_state *state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.command_verb) {
        typecheck_command(state, node);
        handle_command(state, node);
    } else if (symbol == sym.assign_statement) {
        typecheck_assign_statement(state, node);
    } else if (symbol == sym.text_statement) {
        typecheck_text_statement(state, node);
    } else if (symbol == sym.declare_var_statement) {
        collect_declare_var_statement(state, node);
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        scan_for_declarations(state, child);
    }
}

void fuior_lint(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    scan_for_declarations(state, ts_tree_root_node(source_file->tree));
}

fuior_type *fuior_type_new(fuior_state *state, fuior_type_tag tag) {
    fuior_type *type = (fuior_type*)calloc(1, sizeof(fuior_type));
    type->tag = tag;
    fuior_list_push(&state->types, (void*)type);
    return type;
}

void fuior_type_clear(fuior_type *type) {
    free(type->name);
    type->name = NULL;
    if (type->tag == TYPE_ENUM) {
        fuior_map_clear(&type->as_enum.items, false);
    } else if (type->tag == TYPE_UNION || type->tag == TYPE_INTERSECTION) {
        fuior_list_clear_keep_data(&type->as_op.items);
    } else if (type->tag == TYPE_STRING_LITERAL) {
        free(type->as_string_literal.literal);
        type->as_string_literal.literal = NULL;
    }
}

static const char *fuior_type_const_name(fuior_type *type) {
    if (type->name) return type->name;
    switch (type->tag) {
        case TYPE_NIL: return "nil";
        case TYPE_ANY: return "any";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_STRING: return "string";
        case TYPE_NUMBER: return "number";
        case TYPE_ENUM: return "enum";
        default: return NULL;
    }
}

char *fuior_type_name(fuior_type *type) {
    const char *const_name = fuior_type_const_name(type);
    if (const_name != NULL) {
        return fuior_clone_string(const_name);
    }
    if (type->tag == TYPE_STRING_LITERAL) {
        fuior_strlist buffer;
        fuior_strlist_init(&buffer);
        fuior_strlist_push(&buffer, "\"");
        fuior_strlist_push(&buffer, type->as_string_literal.literal);
        fuior_strlist_push(&buffer, "\"");
        char *res = fuior_strlist_concat(&buffer);
        fuior_strlist_clear(&buffer);
        return res;
    }
    if (type->tag == TYPE_UNION || type->tag == TYPE_INTERSECTION) {
        fuior_strlist buffer;
        fuior_strlist_init(&buffer);
        bool first = true;
        const char *sep = type->tag == TYPE_UNION ? " | " : " & ";
        for (fuior_list_item *it = type->as_op.items.first; it; it = it->next) {
            if (first) {
                first = false;
            } else {
                fuior_strlist_push(&buffer, sep);
            }
            fuior_strlist_push_nocopy(&buffer, fuior_type_name((fuior_type*)it->data));
        }
        char *res = fuior_strlist_concat(&buffer);
        fuior_strlist_clear(&buffer);
        return res;
    }
    return NULL;
}

void fuior_command_clear(fuior_command *self) {
    if (self->vararg) {
        free(self->vararg->name);
        free(self->vararg);
        self->vararg = NULL;
    }
    for (fuior_list_item *it = self->args.first; it; it = it->next) {
        free(((fuior_command_arg*)it->data)->name);
    }
    fuior_list_clear(&self->args);
}
