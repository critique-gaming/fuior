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

static void generate_block(fuior_state * state, TSNode node);
static void generate_expression_container(fuior_state * state, TSNode node);
static void generate_expression(fuior_state * state, TSNode node);
static void generate_intl_string(fuior_state * state, TSNode node);

static void generate_debug(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, ts_node_string(node));
}

static void generate_indent(fuior_state * state) {
    for (unsigned i = 0; i < state->indent; i++) {
        fuior_strlist_push(&state->output, "  ");
    }
}

static void generate_literal_token(fuior_state * state, TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    fuior_strlist_push_(&state->output, state->input + start, (end - start));
}

#define generate_number generate_literal_token
#define generate_boolean generate_literal_token
#define generate_identifier generate_literal_token

static void generate_escaped_string(fuior_state * state, const char * string, size_t length) {
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

            fuior_strlist_push(&state->output, escape_sequence);
        }

        if (!escape_sequence && !raw_chunk_start) {
            raw_chunk_start = ptr;
        }
    }

    if (raw_chunk_start) {
        fuior_strlist_push_(&state->output, raw_chunk_start, string + length - raw_chunk_start);
    }
}

static void generate_bare_word(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "\"");
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    generate_escaped_string(state, state->input + start, (end - start));
    fuior_strlist_push(&state->output, "\"");
}

static void generate_string(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "\"");
    size_t start = ts_node_start_byte(node) + 1;
    size_t end = ts_node_end_byte(node) - 1;
    generate_escaped_string(state, state->input + start, (end - start));
    fuior_strlist_push(&state->output, "\"");
}

static void generate_unary_expression(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            fuior_strlist_push_(&state->output, op, end - start);
            fuior_strlist_push(&state->output, " ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym.comment) {
                generate_expression(state, child);
            }
        }
    }

    fuior_strlist_push(&state->output, ")");
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

static void generate_binary_expression(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            fuior_strlist_push(&state->output, " ");

            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            const char * lua_op = translate_binary_operator(op, end - start);

            if (!lua_op) {
                add_error(node, "Unimplemented operator");
                fuior_strlist_push_(&state->output, op, end - start);
            } else {
                fuior_strlist_push(&state->output, lua_op);
            }

            fuior_strlist_push(&state->output, " ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym.comment) {
                generate_expression(state, child);
            }
        }
    }

    fuior_strlist_push(&state->output, ")");
}

static void generate_expression(fuior_state * state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);

    if (symbol == sym.number) {
        generate_number(state, node);
    } else if (symbol == sym.boolean) {
        generate_boolean(state, node);
    } else if (symbol == sym.string) {
        generate_string(state, node);
    } else if (symbol == sym.intl_string) {
        generate_intl_string(state, node);
    } else if (symbol == sym.identifier) {
        fuior_strlist_push(&state->output, "fui.var_get(\"");
        generate_identifier(state, node);
        fuior_strlist_push(&state->output, "\")");
    } else if (symbol == sym.paran_expression) {
        generate_expression_container(state, node);
    } else if (symbol == sym.unary_expression) {
        generate_unary_expression(state, node);
    } else if (symbol == sym.binary_expression) {
        generate_binary_expression(state, node);
    } else {
        add_error(node, "Unimplemented generation");
        generate_debug(state, node);
    }
}

static void generate_text_copy_intl_key(fuior_state * state, TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    uint32_t text_hash = hash(state->input + start, (end - start));
    fuior_strlist_printf(&state->output, "\"%s%06x\"", state->intl_prefix, (unsigned)text_hash & 0xffffff);
}

static void generate_text_copy(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "intl(");
    generate_text_copy_intl_key(state, node);
    fuior_strlist_push(&state->output, ")");
}

static void generate_intl_string_key(fuior_state * state, TSNode node) {
    size_t start = ts_node_start_byte(node) + 2;
    size_t end = ts_node_end_byte(node) - 1;
    uint32_t text_hash = hash(state->input + start, (end - start));
    fuior_strlist_printf(&state->output, "\"%s%06x\"", state->intl_prefix, (unsigned)text_hash & 0xffffff);
}

static void generate_intl_string(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "intl(");
    generate_intl_string_key(state, node);
    fuior_strlist_push(&state->output, ")");
}

static void generate_command_arg(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    if (symbol == sym.bare_word) {
        generate_bare_word(state, child);
    } else {
        generate_expression(state, child);
    }
}

static void generate_command_statement(fuior_state * state, TSNode node) {

    int arg_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.command_verb) {
            if (fuior_get_special_command(state, child, fuior_special_commands_intl) != -1) { return; }
            generate_indent(state);
            fuior_strlist_push(&state->output, "fui.");
            generate_identifier(state, child);
            fuior_strlist_push(&state->output, "(");
        } else if (symbol == sym.command_arg) {
            if (arg_index > 0) {
                fuior_strlist_push(&state->output, ", ");
            }
            generate_command_arg(state, child);
            arg_index += 1;
        }
    }

    fuior_strlist_push(&state->output, ")\n");
}

static void generate_choose_statement(fuior_state * state, TSNode node) {
    unsigned line_no = ts_node_start_point(node).row;

    generate_indent(state);
    fuior_strlist_printf(&state->output, "local choice%u = fui.choose({\n", line_no);

    state->indent += 1;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym.choice) {
            generate_indent(state);

            TSNode text_copy_node = ts_node_child_by_field_id(choice_node, fld.copy);
            TSNode condition_node = ts_node_child_by_field_id(choice_node, fld.condition);
            TSNode meta_node = ts_node_child_by_field_id(choice_node, fld.meta);
            if (!ts_node_is_null(meta_node)) {
                meta_node = ts_node_child_by_field_id(meta_node, fld.block);
            }

            if (!ts_node_is_null(condition_node)) {
                fuior_strlist_push(&state->output, "(");
                generate_expression_container(state, condition_node);
                fuior_strlist_push(&state->output, ") and ");
            }

            if (!ts_node_is_null(meta_node)) {
                fuior_strlist_push(&state->output, "fui.choice_meta(");
            }

            if (!ts_node_is_null(text_copy_node)) {
                generate_text_copy(state, text_copy_node);
            } else {
                fuior_strlist_push(&state->output, "nil");
            }

            if (!ts_node_is_null(meta_node)) {
                fuior_strlist_push(&state->output, ", function ()\n");
                state->indent += 1;
                generate_block(state, meta_node);
                state->indent -= 1;
                generate_indent(state);
                fuior_strlist_push(&state->output, "end)");
            }

            if (!ts_node_is_null(condition_node)) {
                fuior_strlist_push(&state->output, " or nil");
            }

            fuior_strlist_push(&state->output, ",\n");
        }
    }
    state->indent -= 1;

    generate_indent(state);
    fuior_strlist_push(&state->output, "})\n");

    unsigned choice_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym.choice) {
            for (uint32_t j = 0, m = ts_node_named_child_count(choice_node); j < m; j += 1) {
                TSNode text_copy_node = ts_node_named_child(choice_node, j);
                TSSymbol text_copy_symbol = ts_node_symbol(text_copy_node);
                if (text_copy_symbol == sym.block) {
                    generate_indent(state);
                    fuior_strlist_printf(&state->output, "%s choice%u == %u then\n",
                        choice_index ? "elseif" : "if",
                        line_no,
                        choice_index + 1
                    );

                    state->indent += 1;
                    generate_block(state, text_copy_node);
                    state->indent -= 1;

                    choice_index += 1;
                }
            }
        }
    }

    if (choice_index) {
        generate_indent(state);
        fuior_strlist_push(&state->output, "end\n");
    }
}

static void generate_text_statement(fuior_state * state, TSNode node) {
    generate_indent(state);
    fuior_strlist_push(&state->output, "fui.text(\"");

    int has_animation = 0;

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.text_actor) {
            generate_identifier(state, child);
            fuior_strlist_push(&state->output, "\", ");

        } else if (symbol == sym.text_animation) {
            fuior_strlist_push(&state->output, "\"");
            generate_identifier(state, child);
            fuior_strlist_push(&state->output, "\", ");
            has_animation = 1;

        } else if (symbol == sym.text_copy) {
            if (!has_animation) {
                fuior_strlist_push(&state->output, "nil, ");
            }
            generate_text_copy(state, child);
        }
    }

    fuior_strlist_push(&state->output, ")\n");
}

static void generate_expression_container(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    generate_expression(state, child);
}

#define generate_assign_rvalue generate_expression_container
#define generate_condition generate_expression_container

static void generate_assign_statement(fuior_state * state, TSNode node) {
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

    generate_indent(state);
    fuior_strlist_printf(&state->output, "fui.%s(\"", func);
    generate_identifier(state, lvalue_node);
    fuior_strlist_push(&state->output, "\", ");
    generate_assign_rvalue(state, rvalue_node);
    fuior_strlist_push(&state->output, ")\n");
}

static void generate_if_clause(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.block) {
            state->indent += 1;
            generate_block(state, child);
            state->indent -= 1;
        }
    }
}

static void generate_elseif_clause(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.condition) {
            generate_indent(state);
            fuior_strlist_push(&state->output, "elseif ");
            generate_condition(state, child);
            fuior_strlist_push(&state->output, " then\n");
        } else if (symbol == sym.block) {
            state->indent += 1;
            generate_block(state, child);
            state->indent -= 1;
        }
    }
}

static void generate_if_statement(fuior_state * state, TSNode node) {
    generate_indent(state);
    fuior_strlist_push(&state->output, "if ");

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.condition) {
            generate_condition(state, child);
            fuior_strlist_push(&state->output, " then\n");
        } else if (symbol == sym.if_clause) {
            generate_if_clause(state, child);
        } else if (symbol == sym.elseif_clause) {
            generate_elseif_clause(state, child);
        } else if (symbol == sym.else_clause) {
            generate_indent(state);
            fuior_strlist_push(&state->output, "else\n");
            generate_if_clause(state, child);
        }
    }

    generate_indent(state);
    fuior_strlist_push(&state->output, "end\n");
}

static void generate_return_statement(fuior_state * state, TSNode node) {
    generate_indent(state);
    fuior_strlist_push(&state->output, "return");

    bool first = true;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.return_value) {
            fuior_strlist_push(&state->output, first ? " " : ", ");
            generate_expression_container(state, child);
            first = false;
        }
    }

    fuior_strlist_push(&state->output, "\n");
}

static void generate_block(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym.comment) {
        } else if (symbol == sym.command_statement) {
            generate_command_statement(state, child);
        } else if (symbol == sym.text_statement) {
            generate_text_statement(state, child);
        } else if (symbol == sym.assign_statement) {
            generate_assign_statement(state, child);
        } else if (symbol == sym.choose_statement) {
            generate_choose_statement(state, child);
        } else if (symbol == sym.if_statement) {
            generate_if_statement(state, child);
        } else if (symbol == sym.return_statement) {
            generate_return_statement(state, child);
        } else {
            add_error(node, "Unimplemented generation");
            generate_indent(state);
            generate_debug(state, child);
            fuior_strlist_push(&state->output, "\n");
        }
    }
}

static void generate_intl_strings(fuior_state *state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);
    if (symbol == sym.text_copy) {
        generate_indent(state);
        fuior_strlist_push(&state->output, "[");
        generate_text_copy_intl_key(state, node);

        fuior_strlist_push(&state->output, "] = \"");
        size_t start = ts_node_start_byte(node);
        size_t end = ts_node_end_byte(node);
        generate_escaped_string(state, state->input + start, (end - start));
        fuior_strlist_push(&state->output, "\",\n");

    } else if (symbol == sym.intl_string) {
        generate_indent(state);
        fuior_strlist_push(&state->output, "[");
        generate_intl_string_key(state, node);

        fuior_strlist_push(&state->output, "] = \"");
        size_t start = ts_node_start_byte(node) + 2;
        size_t end = ts_node_end_byte(node) - 1;
        generate_escaped_string(state, state->input + start, (end - start));
        fuior_strlist_push(&state->output, "\",\n");
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        generate_intl_strings(state, child);
    }
}

static void generate_source_file(fuior_state * state, TSNode node) {
    fuior_strlist_push(&state->output, "return function (fui)\n");

    state->indent += 1;

    generate_indent(state);
    fuior_strlist_push(&state->output, "local intl = fui.intl(");
    if (state->intl_namespace) {
        fuior_strlist_push(&state->output, "\"");
        generate_escaped_string(state, state->intl_namespace, strlen(state->intl_namespace));
        fuior_strlist_push(&state->output, "\"");
    } else {
        fuior_strlist_push(&state->output, "nil");
    }
    fuior_strlist_push(&state->output, ", {\n");
    state->indent += 1;
    generate_intl_strings(state, node);
    state->indent -= 1;
    generate_indent(state);
    fuior_strlist_push(&state->output, "})\n");

    generate_block(state, node);

    state->indent -= 1;

    fuior_strlist_push(&state->output, "end\n");
}

void fuior_generate_lua(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    generate_source_file(state, ts_tree_root_node(source_file->tree));
}
