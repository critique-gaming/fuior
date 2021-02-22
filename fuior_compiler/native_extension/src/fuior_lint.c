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
    #define CMD_DECLARE_VAR 1
    "declare_var",
    #define CMD_DECLARE_CMD 2
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

        case CMD_DECLARE_VAR: {
            TSNode arg1 = next_node(sym.command_arg, node);
            char * var_name = fuior_command_arg_to_string(state, arg1);
            TSNode arg2 = next_node(sym.command_arg, arg1);
            char * type_name = fuior_command_arg_to_string(state, arg2);
            if (var_name && type_name) {
                fuior_type *var_type;
                var_type = (fuior_type*)fuior_map_get(&state->variables, var_name);
                if (var_type) {
                    add_error(arg1, "variable %s already exists", var_name);
                }
                var_type = (fuior_type*)fuior_map_get(&state->named_types, type_name);
                if (!var_type) {
                    add_error(arg2, "unknown type %s", type_name);
                }
                fuior_map_set(&state->variables, var_name, (void*)var_type);
                fuior_map_set(&state->varname_enum->as_enum.items, var_name, (void*)1);
            } else {
                add_error(node, "declare_var expects var name and type");
            }
            free(var_name);
            free(type_name);
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
                    fuior_type *type = (fuior_type*)fuior_map_get(&state->named_types, argtype);
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

static void typecheck_command(fuior_state *state, TSNode node) {
    char *verb = fuior_node_to_string(state, node);
    fuior_command *cmd = (fuior_command*)fuior_map_get(&state->commands, verb);
    if (!cmd) {
        add_error(node, "unknown command %s", verb);
        free(verb);
        return;
    }

    free(verb);
}

static void scan_for_declarations(fuior_state *state, TSNode node) {
    if (ts_node_symbol(node) == sym.command_verb) {
        typecheck_command(state, node);
        handle_command(state, node);
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
    if (type->tag == TYPE_UNION || type->tag == TYPE_INTERSECTION) {
        fuior_strlist buffer;
        bool first = true;
        const char *sep = type->tag == TYPE_UNION ? " | " : " & ";
        for (fuior_list_item *it = type->as_op.items.first; it; it = it->next) {
            if (!first) {
                first = false;
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
