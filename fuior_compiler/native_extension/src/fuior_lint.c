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
    #define CMD_IMPORT 1
    "import",
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

static fuior_type *type_from_node(fuior_state *state, TSNode node) {
    if (ts_node_is_null(node)) {
        add_error(node, "invalid type expression");
        return NULL;
    }

    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.type_identifier) {
        char *type_name = fuior_node_text(state, node);
        fuior_type * type = (fuior_type*)fuior_map_get(&state->named_types, type_name);
        if (!type) { add_error(node, "undefined type \"%s\"", type_name); }
        free(type_name);
        return type;
    }

    if (symbol == sym.unary_type_expression) {
        TSNode op_node = ts_node_child(node, 0);
        TSNode expr_node = ts_node_child(node, 1);
        if (ts_node_is_null(op_node)) {
            add_error(node, "invalid unary type expression");
            return NULL;
        }

        fuior_type * t = NULL;
        size_t op_len;
        const char * op = fuior_node_text_raw(state, op_node, &op_len);

        if (op_len == 1 && op[0] == '?') {
            fuior_type *child_type = type_from_node(state, expr_node);
            if (child_type) {
                t = fuior_type_new(state, TYPE_UNION);
                fuior_list_push(&t->as_op.items, child_type);
                fuior_list_push(&t->as_op.items, state->type_nil);
            }
        } else {
            add_error(op_node, "unknown unary type operator \"%.*s\"", op_len, op);
        }
        return t;
    }

    if (symbol == sym.binary_type_expression) {
        TSNode expr1_node = ts_node_child(node, 0);
        TSNode op_node = ts_node_child(node, 1);
        TSNode expr2_node = ts_node_child(node, 2);
        if (ts_node_is_null(op_node)) {
            add_error(node, "invalid binary type expression");
            return NULL;
        }

        fuior_type * t = NULL;
        size_t op_len;
        const char * op = fuior_node_text_raw(state, op_node, &op_len);

        if (op_len == 1 && (op[0] == '|' || op[0] == '&')) {
            fuior_type *expr1_type = type_from_node(state, expr1_node);
            fuior_type *expr2_type = type_from_node(state, expr2_node);
            if (expr1_type && expr2_type) {
                t = fuior_type_new(state, op[0] == '|' ? TYPE_UNION : TYPE_INTERSECTION);
                fuior_list_push(&t->as_op.items, expr1_type);
                fuior_list_push(&t->as_op.items, expr2_type);
            }
        } else {
            add_error(op_node, "unknown binary type operator \"%.*s\"", op_len, op);
        }
        return t;
    }

    if (symbol == sym.string) {
        fuior_type * t = fuior_type_new(state, TYPE_STRING_LITERAL);
        t->as_string_literal.literal = fuior_parse_string_node(state, node, &t->as_string_literal.length);
        return t;
    }

    if (symbol == sym.nil) {
        return state->type_nil;
    }

    add_error(node, "unimplemented type expression");
    return NULL;
}

static TSNode first_child(TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }
    return child;
}

static fuior_type *type_from_container(fuior_state * state, TSNode node) {
    return type_from_node(state, first_child(node));
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

        case CMD_IMPORT: {
            TSNode arg1 = next_node(sym.command_arg, node);
            char * filename = fuior_command_arg_to_string(state, arg1);
            if (!filename) {
                add_error(node, "import expects a filename");
                break;
            }

            fuior_import_callback cb = state->on_import;
            void * ctx = state->on_import_ctx;
            if (cb) {
                const char * input = state->input;
                const char * fname = state->filename;
                char * error = cb(filename, state, ctx);
                state->input = input;
                state->filename = fname;
                state->on_import = cb;
                state->on_import_ctx = ctx;

                if (error) {
                  add_error(arg1, "%s", error);
                  free(error);
                }
            }

            break;
        }

    }
}

static fuior_type *type_of_node(fuior_state *state, TSNode node) {
    if (ts_node_is_null(node)) return state->type_any;

    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.boolean) return state->type_boolean;
    if (symbol == sym.nil) return state->type_nil;
    if (symbol == sym.number) return state->type_number;
    if (symbol == sym.intl_string) return state->type_string;

    if (symbol == sym.string) {
        fuior_type *typ = fuior_type_new(state, TYPE_STRING_LITERAL);
        typ->as_string_literal.literal = fuior_parse_string_node(state, node, &typ->as_string_literal.length);
        return typ;
    }

    if (symbol == sym.bare_word) {
        fuior_type *typ = fuior_type_new(state, TYPE_STRING_LITERAL);
        typ->as_string_literal.literal = fuior_node_text_raw(state, node, &typ->as_string_literal.length);
        typ->as_string_literal.foreign_owned = true;
        return typ;
    }

    if (symbol == sym.paran_expression) {
        return type_of_node(state, fuior_skip_comments(ts_node_child(node, 0)));
    }

    if (symbol == sym.identifier) {
        size_t varname_len;
        const char *varname = fuior_node_text_raw(state, node, &varname_len);
        fuior_type * typ = (fuior_type*)fuior_map_get_n(&state->variables, varname, varname_len);
        if (!typ) {
            add_error(node, "undeclared variable \"%.*s\"", varname_len, varname);
        }
        return typ ? typ : state->type_any;
    }

    if (symbol == sym.unary_expression) {
        TSNode op_node = ts_node_child(node, 0);
        TSNode expr_node = ts_node_child(node, 1);

        size_t op_len;
        const char * op = fuior_node_text_raw(state, op_node, &op_len);
        fuior_type *expr_type = type_of_node(state, expr_node);

        // TODO: Properly handle each operator
        return state->type_any;
    }

    if (symbol == sym.binary_expression) {
        TSNode expr1_node = ts_node_child(node, 0);
        TSNode op_node = ts_node_child(node, 1);
        TSNode expr2_node = ts_node_child(node, 2);

        size_t op_len;
        const char * op = fuior_node_text_raw(state, op_node, &op_len);
        fuior_type *expr1_type = type_of_node(state, expr1_node);
        fuior_type *expr2_type = type_of_node(state, expr2_node);

        // TODO: Properly handle each operator
        return state->type_any;
    }

    if (symbol == sym.function_call) {
        TSNode verb_node = ts_node_child_by_field_id(node, fld.name);
        char *name = fuior_node_text(state, verb_node);
        fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, name);
        if (!cmd) {
            add_error(node, "unknown command %s", name);
        }
        free(name);
        return cmd ? cmd->return_type : state->type_any;
    }

    return state->type_any;
}

static fuior_type *type_of_container(fuior_state * state, TSNode node) {
    return type_of_node(state, first_child(node));
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
            return from->as_string_literal.length == to->as_string_literal.length &&
                0 == strncmp(from->as_string_literal.literal, to->as_string_literal.literal, from->as_string_literal.length);
        }
        if (to->tag == TYPE_ENUM) {
            return fuior_map_get_n(&to->as_enum.items, from->as_string_literal.literal, from->as_string_literal.length) != NULL;
        }
        return false;
    }

    return false;
}

static void check_animation(fuior_state *state, TSNode node, const char *actor, size_t actor_len, const char *animation, size_t animation_len) {
    size_t prefix_len = strlen("animation_");
    char *name = (char*)malloc(actor_len + prefix_len + 1);
    strcpy(name, "animation_");
    memcpy(name + prefix_len, actor, actor_len);
    name[prefix_len + actor_len] = '\0';
    fuior_type *anim_enum = (fuior_type*)fuior_map_get(&state->named_types, name);
    free(name);

    if (
        anim_enum == NULL ||
        anim_enum->tag != TYPE_ENUM ||
        fuior_map_get_n(&anim_enum->as_enum.items, animation, animation_len) == NULL
    ) {
        add_error(node, "character \"%.*s\" doesn't have an animation named \"%.*s\"", actor_len, actor, animation_len, animation);
    }
}

static void typecheck_command(fuior_state *state, TSNode node) {
    TSNode verb_node;
    TSNode parent;
    TSNode first_arg;
    bool is_wrapped;
    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.command_verb) {
        verb_node = node;
        parent = ts_node_parent(node);
        first_arg = ts_node_next_named_sibling(node);
        is_wrapped = true;
    } else if (symbol == sym.function_call) {
        verb_node = ts_node_child_by_field_id(node, fld.name);
        parent = node;
        first_arg = ts_node_named_child(ts_node_child_by_field_id(node, fld.arg_list), 0);
        is_wrapped = false;
    }

    if (ts_node_is_null(verb_node)) {
        add_error(node, "invalid command call");
        return;
    }

    char *verb = fuior_node_text(state, verb_node);
    fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, verb);
    if (!cmd) {
        add_error(verb_node, "unknown command %s", verb);
        free(verb);
        return;
    }

    fuior_list_item *cmd_arg_it= cmd->args.first;
    int cmd_arg_count = 0;
    int arg_count = 0;

    bool is_animate = 0 == strcmp("animate", verb);
    const char * animate_actor = NULL;
    size_t animate_actor_len = 0;

    for (
        TSNode it = first_arg;
        !ts_node_is_null(it);
        it = ts_node_next_named_sibling(it)
    ) {
        TSSymbol symbol = ts_node_symbol(it);
        if (is_wrapped && symbol != sym.command_arg) continue;
        if (symbol == sym.comment) continue;

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
            fuior_type *arg_type = type_of_node(state, is_wrapped ? fuior_skip_comments(ts_node_child(it, 0)) : it);
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
                animate_actor_len = arg_type->as_string_literal.length;
            }

            if (is_animate && arg_count == 2 && animate_actor && arg_type->tag == TYPE_STRING_LITERAL) {
                check_animation(state, it,
                    animate_actor, animate_actor_len,
                    arg_type->as_string_literal.literal,
                    arg_type->as_string_literal.length
                );
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

static void typecheck_condition(fuior_state *state, TSNode node) {
    fuior_type *t = type_of_container(state, node);
    if (!can_cast_to(t, state->type_boolean)) {
        char *type_name = fuior_type_name(t);
        add_warning(node, "condition should be boolean. got %s", type_name);
        free(type_name);
    }
}

static void typecheck_return_statement(fuior_state *state, TSNode node) {
    TSNode value_node = ts_node_child_by_field_id(node, fld.return_value);
    fuior_type *t = ts_node_is_null(value_node)
        ? state->type_nil
        : type_of_container(state, node);
    // TODO: Check the return type
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
            assign_name = fuior_node_text(state, it);
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
            assign_op = fuior_node_text(state, it);
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
    const char *actor = NULL;
    size_t actor_len = 0;

    for (
        TSNode it = ts_node_named_child(node, 0);
        !ts_node_is_null(it);
        it = ts_node_next_named_sibling(it)
    ) {
        TSSymbol symbol = ts_node_symbol(it);
        if (symbol == sym.comment) continue;

        if (symbol == sym.text_actor) {
            actor = fuior_node_text_raw(state, it, &actor_len);
            if (!fuior_map_get_n(&state->character_enum->as_enum.items, actor, actor_len)) {
                add_error(it, "no such character \"%.*s\"", actor_len, actor);
                actor = NULL;
            }
        } else if (symbol == sym.text_animation && actor) {
            size_t animation_len;
            const char *animation = fuior_node_text_raw(state, it, &animation_len);
            check_animation(state, it, actor, actor_len, animation, animation_len);
        }
    }
}

static fuior_type *type_from_optional_node_container(fuior_state *state, TSNode node) {
    fuior_type *var_type = NULL;
    if (!ts_node_is_null(node)) {
        var_type = type_from_container(state, node);
    }
    if (var_type == NULL) {
        var_type = state->type_any;
    }
    return var_type;
}

static void collect_declare_var_statement(fuior_state *state, TSNode node) {
    TSNode name_node = ts_node_child_by_field_id(node, fld.name);
    if (ts_node_is_null(name_node)) return;

    TSNode type_node = ts_node_child_by_field_id(node, fld.type);
    fuior_type *var_type = type_from_optional_node_container(state, type_node);

    char *var_name = fuior_node_text(state, name_node);
    if (fuior_map_get(&state->variables, var_name)) {
        add_error(name_node, "variable %s already exists", var_name);
    }

    fuior_map_set(&state->variables, var_name, (void*)var_type);
    fuior_map_set(&state->varname_enum->as_enum.items, var_name, (void*)1);

    TSNode initializer_node = ts_node_child_by_field_id(node, fld.default_value);
    if (!ts_node_is_null(initializer_node)) {
        fuior_type *rvalue_type = type_of_container(state, initializer_node);
        if (!can_cast_to(rvalue_type, var_type)) {
            char *var_type_name = fuior_type_name(var_type);
            char *rvalue_type_name = fuior_type_name(rvalue_type);
            add_error(initializer_node, "trying to assign value of incompatible type to %s: expected %s, got %s", var_name, var_type_name, rvalue_type_name);
            free(var_type_name);
            free(rvalue_type_name);
        }
    }

    free(var_name);
}

static void collect_command_signature(fuior_state *state, TSNode node) {
    TSNode name_node = ts_node_child_by_field_id(node, fld.name);
    if (ts_node_is_null(name_node)) return;

    char *cmd_name = fuior_node_text(state, name_node);
    fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, cmd_name);
    if (cmd) {
        add_error(name_node, "%s command already declared", cmd_name);
        free(cmd_name);
        return;
    }

    cmd = fuior_command_register(state, cmd_name);
    free(cmd_name);

    TSNode arguments_node = ts_node_child_by_field_id(node, fld.arguments);

    for (uint32_t i = 0, n = ts_node_named_child_count(arguments_node); i < n; i += 1) {
        TSNode arg_node = ts_node_named_child(arguments_node, i);
        TSSymbol arg_node_sym = ts_node_symbol(arg_node);

        if (arg_node_sym == sym.arg_definition) {
            TSNode arg_name_node = ts_node_child_by_field_id(arg_node, fld.name);
            if (ts_node_is_null(arg_name_node)) { continue; }

            TSNode arg_type_node = ts_node_child_by_field_id(arg_node, fld.type);
            fuior_type *arg_type = type_from_optional_node_container(state, arg_type_node);

            char *arg_name = fuior_node_text(state, name_node);
            fuior_command_arg *arg = fuior_command_arg_new(arg_name, arg_type);
            free(arg_name);
            fuior_list_push(&cmd->args, (void*)arg);

        } else if (arg_node_sym == sym.vararg_definition) {
            TSNode arg_type_node = ts_node_child_by_field_id(arg_node, fld.type);
            fuior_type *arg_type = type_from_optional_node_container(state, arg_type_node);

            fuior_command_arg *arg = fuior_command_arg_new("...", arg_type);
            cmd->vararg = arg;
        }
    }

    TSNode return_type_node = ts_node_child_by_field_id(node, fld.return_type);
    cmd->return_type = type_from_optional_node_container(state, return_type_node);
}

static void typecheck_string_interpolation(fuior_state *state, TSNode node) {
    fuior_type * type = type_of_container(state, node);
    if (
        !can_cast_to(type, state->type_string) &&
        !can_cast_to(type, state->type_number) &&
        !can_cast_to(type, state->type_boolean)
    ) {
        add_error(node, "string interpolation must resolve to a string, number or boolean");
    }
}

static void scan_for_declarations(fuior_state *state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.command_verb) {
        typecheck_command(state, node);
        handle_command(state, node);
    } else if (symbol == sym.function_call) {
        typecheck_command(state, node);
    } else if (symbol == sym.assign_statement) {
        typecheck_assign_statement(state, node);
    } else if (symbol == sym.text_statement) {
        typecheck_text_statement(state, node);
    } else if (symbol == sym.declare_var_statement) {
        collect_declare_var_statement(state, node);
    } else if (symbol == sym.command_signature) {
        collect_command_signature(state, node);
    } else if (symbol == sym.string_interpolation) {
        typecheck_string_interpolation(state, node);
    } else if (symbol == sym.condition || symbol == sym.choice_condition) {
        typecheck_condition(state, node);
    } else if (symbol == sym.return_statement) {
        typecheck_return_statement(state, node);
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        scan_for_declarations(state, child);
    }
}

void fuior_lint(fuior_state *state, fuior_source_file *source_file, fuior_import_callback import_cb, void* ctx) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    state->on_import = import_cb;
    state->on_import_ctx = ctx;
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
        if (!type->as_string_literal.foreign_owned) {
          free((char*)type->as_string_literal.literal);
        }
        type->as_string_literal.literal = NULL;
        type->as_string_literal.foreign_owned = false;
        type->as_string_literal.length = 0;
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
        fuior_strlist_push_(&buffer, type->as_string_literal.literal, type->as_string_literal.length);
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
