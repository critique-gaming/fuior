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

#define emit(str) fuior_strlist_push(&state->output, (str))

static void emit_block(fuior_state * state, TSNode node);
static void emit_expression_container(fuior_state * state, TSNode node);
static void emit_expression(fuior_state * state, TSNode node);
static void emit_intl_string(fuior_state * state, TSNode node);
static void emit_arg_list(fuior_state *state, TSNode node, bool first);

static void emit_debug(fuior_state * state, TSNode node) {
    emit(ts_node_string(node));
}

static void emit_indent(fuior_state * state) {
    for (unsigned i = 0; i < state->indent; i++) {
        emit("  ");
    }
}

static void emit_literal_token(fuior_state * state, TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    fuior_strlist_push_(&state->output, state->input + start, (end - start));
}

#define emit_number emit_literal_token
#define emit_boolean emit_literal_token
#define emit_identifier emit_literal_token

#define emit_declare_command_statement(state, node) NULL

static void emit_escaped_string(fuior_state * state, const char * string, size_t length) {
    const char * raw_chunk_start = NULL;
    for (const char * ptr = string; ptr < string + length; ptr++) {
        char ch = *ptr;

        const char * escape_sequence = NULL;
        switch (ch) {
            case '\0': escape_sequence = "\\0"; break;
            case '\a': escape_sequence = "\\a"; break;
            case '\b': escape_sequence = "\\b"; break;
            case '\f': escape_sequence = "\\f"; break;
            case '\n': escape_sequence = "\\n"; break;
            case '\r': escape_sequence = "\\r"; break;
            case '\t': escape_sequence = "\\t"; break;
            case '\v': escape_sequence = "\\v"; break;
            case '\\': escape_sequence = "\\\\"; break;
            case '\"': escape_sequence = "\\\""; break;
            case '\'': escape_sequence = "\\'"; break;
        }

        if (escape_sequence) {
            if (raw_chunk_start) {
                fuior_strlist_push_(&state->output, raw_chunk_start, ptr - raw_chunk_start);
                raw_chunk_start = NULL;
            }

            emit(escape_sequence);
        }

        if (!escape_sequence && !raw_chunk_start) {
            raw_chunk_start = ptr;
        }
    }

    if (raw_chunk_start) {
        fuior_strlist_push_(&state->output, raw_chunk_start, string + length - raw_chunk_start);
    }
}

static void emit_bare_word(fuior_state * state, TSNode node) {
    emit("\"");
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    emit_escaped_string(state, state->input + start, (end - start));
    emit("\"");
}

static void emit_string(fuior_state * state, TSNode node) {
    emit("\"");
    size_t len;
    char * s = fuior_parse_string_node(state, node, &len);
    emit_escaped_string(state, s, len);
    free(s);
    emit("\"");
}

static void emit_unary_expression(fuior_state * state, TSNode node) {
    emit("(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            fuior_strlist_push_(&state->output, op, end - start);
            emit(" ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym.comment) {
                emit_expression(state, child);
            }
        }
    }

    emit(")");
}

static const char * translate_binary_operator(const char * op, size_t length) {
    if (0 == strncmp(op, "*", length)) { return "*"; }
    if (0 == strncmp(op, "/", length)) { return "/"; }
    if (0 == strncmp(op, "+", length)) { return "+"; }
    if (0 == strncmp(op, "-", length)) { return "-"; }
    if (0 == strncmp(op, "<", length)) { return "<"; }
    if (0 == strncmp(op, ">", length)) { return ">"; }
    if (0 == strncmp(op, "<=", length)) { return "<="; }
    if (0 == strncmp(op, ">=", length)) { return ">="; }
    if (0 == strncmp(op, "=", length)) { return "=="; }
    if (0 == strncmp(op, "!=", length)) { return "~="; }
    if (0 == strncmp(op, "and", length)) { return "and"; }
    if (0 == strncmp(op, "or", length)) { return "or"; }
    return NULL;
}

static void emit_binary_expression(fuior_state * state, TSNode node) {
    emit("(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            emit(" ");

            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            const char * lua_op = translate_binary_operator(op, end - start);

            if (!lua_op) {
                add_error(node, "Unimplemented operator");
                fuior_strlist_push_(&state->output, op, end - start);
            } else {
                emit(lua_op);
            }

            emit(" ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym.comment) {
                emit_expression(state, child);
            }
        }
    }

    emit(")");
}

static void emit_function_call(fuior_state * state, TSNode node) {
   TSNode name_node = ts_node_child_by_field_id(node, fld.name);
   if (ts_node_is_null(name_node)) { return; }
   emit("fui.");
   emit_identifier(state, name_node);
   emit("(");
   TSNode arg_list_node = ts_node_child_by_field_id(node, fld.arg_list);
   emit_arg_list(state, arg_list_node, true);
   emit(")");
}

static void emit_expression(fuior_state * state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);

    if (symbol == sym.number) {
        emit_number(state, node);
    } else if (symbol == sym.boolean) {
        emit_boolean(state, node);
    } else if (symbol == sym.string) {
        emit_string(state, node);
    } else if (symbol == sym.intl_string) {
        emit_intl_string(state, node);
    } else if (symbol == sym.identifier) {
        emit("fui.var_get(\"");
        emit_identifier(state, node);
        emit("\")");
    } else if (symbol == sym.paran_expression) {
        emit_expression_container(state, node);
    } else if (symbol == sym.unary_expression) {
        emit_unary_expression(state, node);
    } else if (symbol == sym.binary_expression) {
        emit_binary_expression(state, node);
    } else if (symbol == sym.function_call) {
        emit_function_call(state, node);
    } else {
        add_error(node, "Unimplemented generation");
        emit_debug(state, node);
    }
}

static void emit_intl_key(fuior_state * state, const char *s, size_t n) {
    uint32_t text_hash = hash(s, n);
    fuior_strlist_printf(&state->output, "\"%s%06x\"", state->intl_prefix, (unsigned)text_hash & 0xffffff);
}

static void emit_intl_string_key(fuior_state * state, TSNode node) {
    size_t len;
    char * s = fuior_parse_string_node(state, node, &len);
    uint32_t text_hash = hash(s, len);
    emit_intl_key(state, s, len);
    free(s);
}

static void emit_intl_interpolations(fuior_state * state, TSNode node, const char * prefix) {
    int interpolation_count = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.string_interpolation) {
            if (interpolation_count == 0) {
                emit(prefix);
                emit("{\n");
                state->indent += 1;
            }
            emit_indent(state);
            interpolation_count += 1;
            fuior_strlist_printf(&state->output, "arg%d = ", interpolation_count);
            emit_expression_container(state, child);
            emit(",\n");
        }
    }
    if (interpolation_count) {
        state->indent -= 1;
        emit_indent(state);
        emit("}");
    }
}

static void emit_intl_string(fuior_state * state, TSNode node) {
    emit("intl(");
    emit_intl_string_key(state, node);
    emit_intl_interpolations(state, node, ", ");
    emit(")");
}

#define emit_text_copy emit_intl_string

static void emit_command_arg(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    if (symbol == sym.bare_word) {
        emit_bare_word(state, child);
    } else {
        emit_expression(state, child);
    }
}

static void emit_command_statement(fuior_state * state, TSNode node) {

    int arg_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.command_verb) {
            if (fuior_get_special_command(state, child, fuior_special_commands_intl) != -1) { return; }
            emit_indent(state);
            emit("fui.");
            emit_identifier(state, child);
            emit("(");
        } else if (symbol == sym.command_arg) {
            if (arg_index > 0) {
                emit(", ");
            }
            emit_command_arg(state, child);
            arg_index += 1;
        }
    }

    emit(")\n");
}

static void emit_choose_statement(fuior_state * state, TSNode node) {
    unsigned line_no = ts_node_start_point(node).row;

    emit_indent(state);
    fuior_strlist_printf(&state->output, "local choice%u = fui.choose({\n", line_no);

    state->indent += 1;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym.choice) {
            emit_indent(state);

            TSNode text_copy_node = ts_node_child_by_field_id(choice_node, fld.copy);
            TSNode condition_node = ts_node_child_by_field_id(choice_node, fld.condition);
            TSNode meta_node = ts_node_child_by_field_id(choice_node, fld.meta);
            if (!ts_node_is_null(meta_node)) {
                meta_node = ts_node_child_by_field_id(meta_node, fld.block);
            }

            if (!ts_node_is_null(condition_node)) {
                emit("(");
                emit_expression_container(state, condition_node);
                emit(") and ");
            }

            if (!ts_node_is_null(meta_node)) {
                emit("fui.choice_meta(");
            }

            if (!ts_node_is_null(text_copy_node)) {
                emit_text_copy(state, text_copy_node);
            } else {
                emit("nil");
            }

            if (!ts_node_is_null(meta_node)) {
                emit(", function ()\n");
                state->indent += 1;
                emit_block(state, meta_node);
                state->indent -= 1;
                emit_indent(state);
                emit("end)");
            }

            if (!ts_node_is_null(condition_node)) {
                emit(" or nil");
            }

            emit(",\n");
        }
    }
    state->indent -= 1;

    emit_indent(state);
    emit("})\n");

    unsigned choice_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym.choice) {
            for (uint32_t j = 0, m = ts_node_named_child_count(choice_node); j < m; j += 1) {
                TSNode text_copy_node = ts_node_named_child(choice_node, j);
                TSSymbol text_copy_symbol = ts_node_symbol(text_copy_node);
                if (text_copy_symbol == sym.block) {
                    emit_indent(state);
                    fuior_strlist_printf(&state->output, "%s choice%u == %u then\n",
                        choice_index ? "elseif" : "if",
                        line_no,
                        choice_index + 1
                    );

                    state->indent += 1;
                    emit_block(state, text_copy_node);
                    state->indent -= 1;

                    choice_index += 1;
                }
            }
        }
    }

    if (choice_index) {
        emit_indent(state);
        emit("end\n");
    }
}

static void emit_text_statement(fuior_state * state, TSNode node) {
    emit_indent(state);
    emit("fui.text(\"");

    int has_animation = 0;

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.text_actor) {
            emit_identifier(state, child);
            emit("\", ");

        } else if (symbol == sym.text_animation) {
            emit("\"");
            emit_identifier(state, child);
            emit("\", ");
            has_animation = 1;

        } else if (symbol == sym.text_copy) {
            if (!has_animation) {
                emit("nil, ");
            }
            emit_intl_string_key(state, child);
            emit_intl_interpolations(state, child, ", ");
        }
    }

    emit(")\n");
}

static void emit_expression_container(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    emit_expression(state, child);
}

#define emit_assign_rvalue emit_expression_container
#define emit_condition emit_expression_container

static void emit_assign_statement(fuior_state * state, TSNode node) {
    TSNode lvalue_node, rvalue_node;
    char op = 0;

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.assign_lvalue) {
            lvalue_node = child;
        } else if (symbol == sym.assign_operator) {
            op = state->input[ts_node_start_byte(child)];
        } else if (symbol == sym.assign_rvalue) {
            rvalue_node = child;
        }
    }


    const char * func = NULL;
    switch (op) {
        case '+': { func = "var_increment"; break; }
        case '-': { func = "var_decrement"; break; }
        case '=': { func = "var_set"; break; }
    }

    emit_indent(state);
    fuior_strlist_printf(&state->output, "fui.%s(\"", func);
    emit_identifier(state, lvalue_node);
    emit("\", ");
    emit_assign_rvalue(state, rvalue_node);
    emit(")\n");
}

static void emit_if_clause(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.block) {
            state->indent += 1;
            emit_block(state, child);
            state->indent -= 1;
        }
    }
}

static void emit_elseif_clause(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.condition) {
            emit_indent(state);
            emit("elseif ");
            emit_condition(state, child);
            emit(" then\n");
        } else if (symbol == sym.block) {
            state->indent += 1;
            emit_block(state, child);
            state->indent -= 1;
        }
    }
}

static void emit_if_statement(fuior_state * state, TSNode node) {
    emit_indent(state);
    emit("if ");

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.condition) {
            emit_condition(state, child);
            emit(" then\n");
        } else if (symbol == sym.if_clause) {
            emit_if_clause(state, child);
        } else if (symbol == sym.elseif_clause) {
            emit_elseif_clause(state, child);
        } else if (symbol == sym.else_clause) {
            emit_indent(state);
            emit("else\n");
            emit_if_clause(state, child);
        }
    }

    emit_indent(state);
    emit("end\n");
}

static void emit_return_statement(fuior_state * state, TSNode node) {
    emit_indent(state);
    emit("return");

    bool first = true;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.return_value) {
            emit(first ? " " : ", ");
            emit_expression_container(state, child);
            first = false;
        }
    }

    emit("\n");
}

static void emit_arg_list(fuior_state *state, TSNode node, bool first) {
    for (uint32_t j = 0, m = ts_node_named_child_count(node); j < m; j += 1) {
        TSNode arg_node = ts_node_named_child(node, j);
        if (ts_node_symbol(arg_node) != sym.comment) {
            if (!first) emit(", ");
            first = false;
            emit_expression(state, arg_node);
        }
    }
}

static void emit_declare_var_statement(fuior_state * state, TSNode node) {
    TSNode name_node = ts_node_child_by_field_id(node, fld.name);
    TSNode default_value_node = ts_node_child_by_field_id(node, fld.default_value);
    if (ts_node_is_null(name_node)) {
        add_error(node, "Invalid variable declaration");
        return;
    }

    emit_indent(state);
    emit("fui.declare_var(\"");
    emit_identifier(state, name_node);
    emit("\", ");
    if (ts_node_is_null(default_value_node)) {
        emit("nil");
    } else {
        emit_expression_container(state, default_value_node);
    }

    bool first = true;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.declare_var_decorator) {
            TSNode decorator_name_node = ts_node_child_by_field_id(child, fld.name);
            if (ts_node_is_null(decorator_name_node)) continue;

            emit(first ? ", {{\"" : ", {\"");
            first = false;
            emit_identifier(state, decorator_name_node);
            emit("\"");

            TSNode arg_list_node = ts_node_child_by_field_id(child, fld.arg_list);
            emit_arg_list(state, arg_list_node, false);

            emit("}");
        }
    }

    if (!first) { emit("}"); }
    emit(")\n");
}

static void emit_arg_definition_list(fuior_state * state, TSNode node) {
    if (ts_node_is_null(node)) return;
    bool first = true;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.arg_definition) {
            TSNode name_node = ts_node_child_by_field_id(child, fld.name);
            if (!ts_node_is_null(name_node)) {
                if (!first) emit(", ");
                first = false;
                emit_identifier(state, name_node);
            }
        } else if (symbol == sym.vararg_definition) {
            emit(first ? "..." : ", ...");
            first = false;
        }
    }
}

static void emit_define_command_statement(fuior_state * state, TSNode node) {
    TSNode signature_node = ts_node_child_by_field_id(node, fld.signature);
    TSNode name_node = ts_node_child_by_field_id(signature_node, fld.name);
    TSNode arg_list_node = ts_node_child_by_field_id(signature_node, fld.arguments);
    TSNode body_node = ts_node_child_by_field_id(node, fld.body);

    if (ts_node_is_null(body_node) || ts_node_is_null(name_node)) {
        add_error(node, "Invalid define command statement");
        return;
    }

    emit_indent(state);
    emit("fui.define_command(\"");
    emit_identifier(state, name_node);
    emit("\", function (");
    emit_arg_definition_list(state, arg_list_node);
    emit(")\n");
    state->indent += 1;
    emit_block(state, body_node);
    state->indent -= 1;
    emit_indent(state);
    emit("end)\n");
}

static void emit_block(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.comment) {
        } else if (symbol == sym.command_statement) {
            emit_command_statement(state, child);
        } else if (symbol == sym.text_statement) {
            emit_text_statement(state, child);
        } else if (symbol == sym.assign_statement) {
            emit_assign_statement(state, child);
        } else if (symbol == sym.choose_statement) {
            emit_choose_statement(state, child);
        } else if (symbol == sym.if_statement) {
            emit_if_statement(state, child);
        } else if (symbol == sym.declare_var_statement) {
            emit_declare_var_statement(state, child);
        } else if (symbol == sym.declare_command_statement) {
            emit_declare_command_statement(state, child);
        } else if (symbol == sym.define_command_statement) {
            emit_define_command_statement(state, child);
        } else if (symbol == sym.return_statement) {
            emit_return_statement(state, child);
        } else {
            add_error(node, "Unimplemented generation");
            emit_indent(state);
            emit_debug(state, child);
            emit("\n");
        }
    }
}

static void emit_intl_strings(fuior_state *state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.text_copy || symbol == sym.intl_string) {
        size_t len;
        char * s = fuior_parse_string_node(state, node, &len);

        emit_indent(state);
        emit("[");
        emit_intl_key(state, s, len);
        emit("] = \"");
        emit_escaped_string(state, s, len);
        emit("\",\n");

        free(s);
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        emit_intl_strings(state, child);
    }
}

static void emit_source_file(fuior_state * state, TSNode node) {
    emit("return function (fui)\n");

    state->indent += 1;

    emit_indent(state);
    emit("local intl = fui.intl(");
    if (state->intl_namespace) {
        emit("\"");
        emit_escaped_string(state, state->intl_namespace, strlen(state->intl_namespace));
        emit("\"");
    } else {
        emit("nil");
    }
    emit(", {\n");
    state->indent += 1;
    emit_intl_strings(state, node);
    state->indent -= 1;
    emit_indent(state);
    emit("})\n");

    emit_block(state, node);

    state->indent -= 1;

    emit("end\n");
}

void fuior_emit_lua(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    emit_source_file(state, ts_tree_root_node(source_file->tree));
}
