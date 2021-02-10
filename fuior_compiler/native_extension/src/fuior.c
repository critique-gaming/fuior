#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <tree_sitter/api.h>

#include "fuior.h"
#include "fuior_list.h"

struct fuior_state {
    const char * input;
    fuior_list output;

    const char * filename;
    char * intl_namespace;
    char * intl_prefix;
    unsigned indent;

    fuior_list errors;
    fuior_list warnings;
};

#ifdef __cplusplus
extern "C"
#endif
const TSLanguage *tree_sitter_fuior();

static const char * const special_commands[] = {
    #define CMD_INTL_NAMESPACE 0
    "intl_namespace",

    #define CMD_INTL_PREFIX 1
    "intl_prefix",

    NULL
};

static const TSLanguage * fuior_language = NULL;
static TSSymbol sym_ERROR;
static TSSymbol sym_comment;
static TSSymbol sym_command;
static TSSymbol sym_command_verb;
static TSSymbol sym_command_arg;
static TSSymbol sym_bare_word;
static TSSymbol sym_number;
static TSSymbol sym_string;
static TSSymbol sym_boolean;
static TSSymbol sym_identifier;
static TSSymbol sym_unary_expression;
static TSSymbol sym_binary_expression;
static TSSymbol sym_paran_expression;
static TSSymbol sym_choose_statement;
static TSSymbol sym_choice;
static TSSymbol sym_choice_condition;
static TSSymbol sym_block;
static TSSymbol sym_text_copy;
static TSSymbol sym_show_text;
static TSSymbol sym_text_actor;
static TSSymbol sym_text_animation;
static TSSymbol sym_stat_operation;
static TSSymbol sym_stat_lvalue;
static TSSymbol sym_stat_operator;
static TSSymbol sym_stat_rvalue;
static TSSymbol sym_if_statement;
static TSSymbol sym_condition;
static TSSymbol sym_if_clause;
static TSSymbol sym_elseif_clause;
static TSSymbol sym_else_clause;

#define add_error(node, message) do { \
    TSPoint point = ts_node_start_point(node); \
    fuior_list_printf(&state->errors, "%s:%u:%u " message, \
        state->filename, (unsigned)point.row, (unsigned)point.column \
    ); \
} while (0)

#define add_warning(node, message) do { \
    TSPoint point = ts_node_start_point(node); \
    fuior_list_printf(&state->warnings, "%s:%u:%u " message, \
        state->filename, (unsigned)point.row, (unsigned)point.column \
    ); \
} while (0)

static void generate_block(fuior_state * state, TSNode node);
static void generate_expression_container(fuior_state * state, TSNode node);
static void generate_expression(fuior_state * state, TSNode node);
static int get_special_command(fuior_state * state, TSNode command_verb);
static uint32_t hash(const char * data, size_t length);

static void generate_debug(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, ts_node_string(node));
}

static void generate_indent(fuior_state * state) {
    for (unsigned i = 0; i < state->indent; i++) {
        fuior_list_push(&state->output, "  ");
    }
}

static void generate_literal_token(fuior_state * state, TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    fuior_list_push_(&state->output, state->input + start, (end - start));
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
                fuior_list_push_(&state->output, raw_chunk_start, ptr - raw_chunk_start);
                raw_chunk_start = NULL;
            }

            fuior_list_push(&state->output, escape_sequence);
        }

        if (!escape_sequence && !raw_chunk_start) {
            raw_chunk_start = ptr;
        }
    }

    if (raw_chunk_start) {
        fuior_list_push_(&state->output, raw_chunk_start, string + length - raw_chunk_start);
    }
}

static void generate_bare_word(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, "\"");
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    generate_escaped_string(state, state->input + start, (end - start));
    fuior_list_push(&state->output, "\"");
}

static void generate_string(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, "\"");
    size_t start = ts_node_start_byte(node) + 1;
    size_t end = ts_node_end_byte(node) - 1;
    generate_escaped_string(state, state->input + start, (end - start));
    fuior_list_push(&state->output, "\"");
}

static void generate_unary_expression(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, "(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            fuior_list_push_(&state->output, op, end - start);
            fuior_list_push(&state->output, " ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym_comment) {
                generate_expression(state, child);
            }
        }
    }

    fuior_list_push(&state->output, ")");
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
    fuior_list_push(&state->output, "(");

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);

        if (!ts_node_is_named(child)) {
            fuior_list_push(&state->output, " ");

            uint32_t start = ts_node_start_byte(child);
            uint32_t end = ts_node_end_byte(child);
            const char * op = state->input + start;
            const char * lua_op = translate_binary_operator(op, end - start);

            if (!lua_op) {
                add_error(node, "Unimplemented operator");
                fuior_list_push_(&state->output, op, end - start);
            } else {
                fuior_list_push(&state->output, lua_op);
            }

            fuior_list_push(&state->output, " ");
        } else {
            TSSymbol symbol = ts_node_symbol(child);
            if (symbol != sym_comment) {
                generate_expression(state, child);
            }
        }
    }

    fuior_list_push(&state->output, ")");
}

static void generate_expression(fuior_state * state, TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);

    if (symbol == sym_number) {
        generate_number(state, node);
    } else if (symbol == sym_boolean) {
        generate_boolean(state, node);
    } else if (symbol == sym_string) {
        generate_string(state, node);
    } else if (symbol == sym_identifier) {
        fuior_list_push(&state->output, "fui.var_get(\"");
        generate_identifier(state, node);
        fuior_list_push(&state->output, "\")");
    } else if (symbol == sym_paran_expression) {
        generate_expression_container(state, node);
    } else if (symbol == sym_unary_expression) {
        generate_unary_expression(state, node);
    } else if (symbol == sym_binary_expression) {
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
    fuior_list_printf(&state->output, "\"%s%06x\"", state->intl_prefix, (unsigned)text_hash & 0xffffff);
}

static void generate_text_copy(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, "intl(");
    generate_text_copy_intl_key(state, node);
    fuior_list_push(&state->output, ")");
}

static void generate_command_arg(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym_comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    if (symbol == sym_bare_word) {
        generate_bare_word(state, child);
    } else {
        generate_expression(state, child);
    }
}

static int get_special_command(fuior_state * state, TSNode command_verb) {
    size_t start = ts_node_start_byte(command_verb);
    size_t end = ts_node_end_byte(command_verb);
    size_t len = end - start;
    const char * str = state->input + start;

    for (int i = 0; special_commands[i]; i++) {
        if (strncmp(str, special_commands[i], len) == 0) {
            return i;
        }
    }

    return -1;
}

static void generate_command(fuior_state * state, TSNode node) {

    int arg_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_command_verb) {
            if (get_special_command(state, child) != -1) { return; }
            generate_indent(state);
            fuior_list_push(&state->output, "fui.");
            generate_identifier(state, child);
            fuior_list_push(&state->output, "(");
        } else if (symbol == sym_command_arg) {
            if (arg_index > 0) {
                fuior_list_push(&state->output, ", ");
            }
            generate_command_arg(state, child);
            arg_index += 1;
        }
    }

    fuior_list_push(&state->output, ")\n");
}

static void generate_choose_statement(fuior_state * state, TSNode node) {
    unsigned line_no = ts_node_start_point(node).row;

    generate_indent(state);
    fuior_list_printf(&state->output, "local choice%u = fui.choose({\n", line_no);

    state->indent += 1;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym_choice) {
            generate_indent(state);
            int has_condition = false;
            for (uint32_t j = 0, m = ts_node_named_child_count(choice_node); j < m; j += 1) {
                TSNode text_copy_node = ts_node_named_child(choice_node, j);
                TSSymbol text_copy_symbol = ts_node_symbol(text_copy_node);
                if (text_copy_symbol == sym_choice_condition) {
                    has_condition = 1;
                    fuior_list_push(&state->output, "(");
                    generate_expression_container(state, text_copy_node);
                    fuior_list_push(&state->output, ") and ");
                }
                if (text_copy_symbol == sym_text_copy) {
                    generate_text_copy(state, text_copy_node);
                }
            }
            if (has_condition) { fuior_list_push(&state->output, " or nil"); }
            fuior_list_push(&state->output, ",\n");
        }
    }
    state->indent -= 1;

    generate_indent(state);
    fuior_list_push(&state->output, "})\n");

    unsigned choice_index = 0;
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode choice_node = ts_node_named_child(node, i);
        TSSymbol choice_symbol = ts_node_symbol(choice_node);
        if (choice_symbol == sym_choice) {
            for (uint32_t j = 0, m = ts_node_named_child_count(choice_node); j < m; j += 1) {
                TSNode text_copy_node = ts_node_named_child(choice_node, j);
                TSSymbol text_copy_symbol = ts_node_symbol(text_copy_node);
                if (text_copy_symbol == sym_block) {
                    generate_indent(state);
                    fuior_list_printf(&state->output, "%s choice%u == %u then\n",
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
        fuior_list_push(&state->output, "end\n");
    }
}

static void generate_show_text(fuior_state * state, TSNode node) {
    generate_indent(state);
    fuior_list_push(&state->output, "fui.text(\"");

    int has_animation = 0;

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_text_actor) {
            generate_identifier(state, child);
            fuior_list_push(&state->output, "\", ");

        } else if (symbol == sym_text_animation) {
            fuior_list_push(&state->output, "\"");
            generate_identifier(state, child);
            fuior_list_push(&state->output, "\", ");
            has_animation = 1;

        } else if (symbol == sym_text_copy) {
            if (!has_animation) {
                fuior_list_push(&state->output, "nil, ");
            }
            generate_text_copy(state, child);
        }
    }

    fuior_list_push(&state->output, ")\n");
}

static void generate_expression_container(fuior_state * state, TSNode node) {
    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym_comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    generate_expression(state, child);
}

#define generate_stat_rvalue generate_expression_container
#define generate_condition generate_expression_container

static void generate_stat_operation(fuior_state * state, TSNode node) {
    TSNode lvalue_node, rvalue_node;
    char op = 0;

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_stat_lvalue) {
            lvalue_node = child;
        } else if (symbol == sym_stat_operator) {
            op = state->input[ts_node_start_byte(child)];
        } else if (symbol == sym_stat_rvalue) {
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
    fuior_list_printf(&state->output, "fui.%s(\"", func);
    generate_identifier(state, lvalue_node);
    fuior_list_push(&state->output, "\", ");
    generate_stat_rvalue(state, rvalue_node);
    fuior_list_push(&state->output, ")\n");
}

static void generate_if_clause(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_block) {
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
        if (symbol == sym_condition) {
            generate_indent(state);
            fuior_list_push(&state->output, "elseif ");
            generate_condition(state, child);
            fuior_list_push(&state->output, " then\n");
        } else if (symbol == sym_block) {
            state->indent += 1;
            generate_block(state, child);
            state->indent -= 1;
        }
    }
}

static void generate_if_statement(fuior_state * state, TSNode node) {
    generate_indent(state);
    fuior_list_push(&state->output, "if ");

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_condition) {
            generate_condition(state, child);
            fuior_list_push(&state->output, " then\n");
        } else if (symbol == sym_if_clause) {
            generate_if_clause(state, child);
        } else if (symbol == sym_elseif_clause) {
            generate_elseif_clause(state, child);
        } else if (symbol == sym_else_clause) {
            generate_indent(state);
            fuior_list_push(&state->output, "else\n");
            generate_if_clause(state, child);
        }
    }

    generate_indent(state);
    fuior_list_push(&state->output, "end\n");
}

static void generate_block(fuior_state * state, TSNode node) {
    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);

        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == sym_comment) {
        } else if (symbol == sym_command) {
            generate_command(state, child);
        } else if (symbol == sym_show_text) {
            generate_show_text(state, child);
        } else if (symbol == sym_stat_operation) {
            generate_stat_operation(state, child);
        } else if (symbol == sym_choose_statement) {
            generate_choose_statement(state, child);
        } else if (symbol == sym_if_statement) {
            generate_if_statement(state, child);
        } else {
            add_error(node, "Unimplemented generation");
            generate_indent(state);
            generate_debug(state, child);
            fuior_list_push(&state->output, "\n");
        }
    }
}

static void generate_intl_strings(fuior_state *state, TSNode node) {
    if (ts_node_symbol(node) == sym_text_copy) {
        generate_indent(state);
        fuior_list_push(&state->output, "[");
        generate_text_copy_intl_key(state, node);

        fuior_list_push(&state->output, "] = \"");
        size_t start = ts_node_start_byte(node);
        size_t end = ts_node_end_byte(node);
        generate_escaped_string(state, state->input + start, (end - start));
        fuior_list_push(&state->output, "\",\n");
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        generate_intl_strings(state, child);
    }
}

static void generate_source_file(fuior_state * state, TSNode node) {
    fuior_list_push(&state->output, "return function (fui)\n");

    state->indent += 1;

    generate_indent(state);
    fuior_list_push(&state->output, "local intl = fui.intl(");
    if (state->intl_namespace) {
        fuior_list_push(&state->output, "\"");
        generate_escaped_string(state, state->intl_namespace, strlen(state->intl_namespace));
        fuior_list_push(&state->output, "\"");
    } else {
        fuior_list_push(&state->output, "nil");
    }
    fuior_list_push(&state->output, ", {\n");
    state->indent += 1;
    generate_intl_strings(state, node);
    state->indent -= 1;
    generate_indent(state);
    fuior_list_push(&state->output, "})\n");

    generate_block(state, node);

    state->indent -= 1;

    fuior_list_push(&state->output, "end\n");
}

static void scan_for_syntax_errors(fuior_state *state, TSNode node) {
    if (ts_node_symbol(node) == sym_ERROR) {
        add_error(node, "Parser error");
        return;
    }

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);
        scan_for_syntax_errors(state, child);
    }
}

static char * command_arg_to_string(fuior_state *state, TSNode node) {
    while (1) {
        if (ts_node_is_null(node)) { return NULL; }
        if (ts_node_symbol(node) == sym_command_arg) { break; }
        node = ts_node_next_named_sibling(node);
    }

    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym_comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    size_t start = 0;
    size_t end = 0;
    if (symbol == sym_bare_word) {
        start = ts_node_start_byte(child);
        end = ts_node_end_byte(child);
    } else if (symbol == sym_string) {
        start = ts_node_start_byte(child) + 1;
        end = ts_node_end_byte(child) - 1;
    } else {
        return NULL;
    }

    char * res = (char*)malloc(end - start + 1);
    memcpy(res, state->input + start, end - start);
    res[end - start] = 0;
    return res;
}

static void scan_for_special_commands(fuior_state *state, TSNode node) {
    if (ts_node_symbol(node) == sym_command_verb) {
        int cmd = get_special_command(state, node);
        switch (cmd) {
            case -1: break;
            case CMD_INTL_NAMESPACE: {
                state->intl_namespace = command_arg_to_string(state, ts_node_next_named_sibling(node));
                break;
            }
            case CMD_INTL_PREFIX: {
                state->intl_prefix = command_arg_to_string(state, ts_node_next_named_sibling(node));
                break;
            }
        }
    }

    for (uint32_t i = 0, n = ts_node_named_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_named_child(node, i);
        scan_for_special_commands(state, child);
    }
}

static uint32_t hash(const char * data, size_t length) {
    uint32_t hashAddress = 0;
    for (size_t i = 0; i < length; i++){
        hashAddress = data[i] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
    return hashAddress;
}

static char * default_intl_prefix(const char * filename) {
    char * res = NULL;

    size_t len = strlen(filename);
    if (len == 0) {
        res = (char*)malloc(1);
        res[0] = 0;
        return res;
    }

    const char * basename = filename + len;
    while (1) {
        const char * peek = basename - 1;
        if (peek < filename || *peek == '/' || *peek == '\\') {
            break;
        }
        basename = peek;
    }

    size_t strip_skip = 0;
    if (basename == filename) {
        res = (char*)malloc(len + 2);
        strncpy(res, filename, len + 2);
        res[len] = '.';
        res[len + 1] = 0;
    } else {
        uint32_t dirname_hash = hash(filename, basename - filename);

        size_t basename_len = len - (basename - filename);
        res = (char*)malloc(9 + basename_len);
        snprintf(res, 9 + basename_len, "%06x.%s.", ((unsigned)dirname_hash) & 0xffffff, basename);
        strip_skip = 7;
    }

    // Strip file extension
    for (size_t i = strip_skip; res[i] && res[i + 1]; i++) {
        if (res[i] == '.') {
            res[i + 1] = 0;
            break;
        }
    }

    return res;
}

void fuior_check_syntax(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    scan_for_syntax_errors(state, ts_tree_root_node(source_file->tree));
}

void fuior_analyse(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    scan_for_special_commands(state, ts_tree_root_node(source_file->tree));
    if (!state->intl_prefix) {
        state->intl_prefix = default_intl_prefix(source_file->filename);
    }
}

void fuior_lint(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
}

void fuior_generate(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    generate_source_file(state, ts_tree_root_node(source_file->tree));
}

TSParser* fuior_parser_new() {
    if (!fuior_language) {
      fuior_language = tree_sitter_fuior();

      #define fetch_symbol(symbol) sym_ ## symbol = ts_language_symbol_for_name(fuior_language, #symbol)

      fetch_symbol(ERROR);
      fetch_symbol(comment);
      fetch_symbol(command);
      fetch_symbol(command_verb);
      fetch_symbol(command_arg);
      fetch_symbol(bare_word);
      fetch_symbol(number);
      fetch_symbol(string);
      fetch_symbol(boolean);
      fetch_symbol(identifier);
      fetch_symbol(unary_expression);
      fetch_symbol(binary_expression);
      fetch_symbol(paran_expression);
      fetch_symbol(choose_statement);
      fetch_symbol(choice);
      fetch_symbol(choice_condition);
      fetch_symbol(block);
      fetch_symbol(text_copy);
      fetch_symbol(show_text);
      fetch_symbol(text_actor);
      fetch_symbol(text_animation);
      fetch_symbol(stat_operation);
      fetch_symbol(stat_lvalue);
      fetch_symbol(stat_operator);
      fetch_symbol(stat_rvalue);
      fetch_symbol(if_statement);
      fetch_symbol(condition);
      fetch_symbol(if_clause);
      fetch_symbol(elseif_clause);
      fetch_symbol(else_clause);
    }

    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, fuior_language);

    return parser;
}

fuior_state *fuior_state_new() {
    fuior_state *state = (fuior_state*)calloc(1, sizeof(fuior_state));
    return state;
}

bool fuior_state_has_errors(const fuior_state *state) {
    return state->errors.first != NULL;
}

void fuior_state_free(fuior_state *state) {
    free(state->intl_prefix);
    free(state->intl_namespace);
    free(state);
}

void fuior_parse(fuior_source_file *sourcefile, TSParser *parser, const char * input, size_t input_len, const char * filename, TSTree *previous_tree) {
    if (!filename) { filename = "source"; }
    sourcefile->filename = filename;
    sourcefile->input = input;
    sourcefile->input_len = input_len;
    sourcefile->tree = ts_parser_parse_string(parser, previous_tree, input, input_len);
}

fuior_results *fuior_compile(const char * input, size_t input_len, const char * filename) {
    TSParser *parser = fuior_parser_new();

    fuior_source_file source_file;
    fuior_parse(&source_file, parser, input, input_len, filename, NULL);

    fuior_state *state = fuior_state_new();

    fuior_check_syntax(state, &source_file);
    if (!fuior_state_has_errors(state)) {
        fuior_analyse(state, &source_file);
    }
    if (!fuior_state_has_errors(state)) {
        fuior_generate(state, &source_file);
    }

    fuior_results *results = (fuior_results *)calloc(1, sizeof(fuior_results));
    fuior_state_get_results(state, results);

    ts_tree_delete(source_file.tree);
    ts_parser_delete(parser);

    return results;
}

void fuior_state_get_results(fuior_state *state, fuior_results * results) {
    results->output = fuior_list_concat(&state->output);

    fuior_list_to_array(&state->errors, &results->errors, &results->error_count);
    fuior_list_to_array(&state->warnings, &results->warnings, &results->warning_count);

    fuior_list_clear(&state->output);
    fuior_list_clear_keep_data(&state->errors);
    fuior_list_clear_keep_data(&state->warnings);
}

void fuior_results_free(fuior_results * results) {
    if (!results) { return; }

    free(results->output);

    for (size_t i = 0; i < results->error_count; i++) {
        free(results->errors[i]);
    }
    free(results->errors);

    for (size_t i = 0; i < results->warning_count; i++) {
        free(results->warnings[i]);
    }
    free(results->warnings);
}
