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

#ifdef __cplusplus
extern "C" {
#endif

const TSLanguage *tree_sitter_fuior();

static const TSLanguage * fuior_language = NULL;
fuior_tree_sitter_symbols_t fuior_tree_sitter_symbols;

int fuior_get_special_command(fuior_state * state, TSNode command_verb, const char * const *special_commands) {
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

fuior_message *fuior_message_create(const char *filename, TSNode node, const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char * buffer = (char*)malloc(length + 1);
    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    fuior_message *msg = (fuior_message*)malloc(sizeof(fuior_message));
    msg->message = buffer;

    TSPoint start_point = ts_node_start_point(node);
    msg->start_row = start_point.row;
    msg->start_column = start_point.column;

    TSPoint end_point = ts_node_end_point(node);
    msg->end_row = end_point.row;
    msg->end_column = end_point.column;

    msg->filename = filename;

    return msg;
}

static void scan_for_syntax_errors(fuior_state *state, TSNode node) {
    if (ts_node_symbol(node) == sym.ERROR) {
        add_error(node, "Parser error");
        return;
    }

    for (uint32_t i = 0, n = ts_node_child_count(node); i < n; i += 1) {
        TSNode child = ts_node_child(node, i);
        scan_for_syntax_errors(state, child);
    }
}

void fuior_check_syntax(fuior_state *state, fuior_source_file *source_file) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    scan_for_syntax_errors(state, ts_tree_root_node(source_file->tree));
}

TSParser* fuior_parser_new() {
    if (!fuior_language) {
      fuior_language = tree_sitter_fuior();

      #define fetch_symbol(symbol) sym. symbol = ts_language_symbol_for_name(fuior_language, #symbol)

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

    fuior_type *string_type = fuior_type_new(state, TYPE_STRING);
    fuior_type *any_type = fuior_type_new(state, TYPE_ANY);
    fuior_map_set(&state->named_types, "string", string_type);
    fuior_map_set(&state->named_types, "nil", fuior_type_new(state, TYPE_NIL));
    fuior_map_set(&state->named_types, "boolean", fuior_type_new(state, TYPE_BOOLEAN));
    fuior_map_set(&state->named_types, "number", fuior_type_new(state, TYPE_NUMBER));
    fuior_map_set(&state->named_types, "any", any_type);

    fuior_type *varname_type = fuior_type_new(state, TYPE_ENUM);
    varname_type->name = fuior_clone_string("varname");
    fuior_map_set(&state->named_types, "varname", varname_type);
    state->varname_enum = varname_type;

    fuior_command *enum_cmd = fuior_command_register(state, "enum");
    fuior_list_push(&enum_cmd->args, fuior_command_arg_new("enum_name", string_type));
    fuior_list_push(&enum_cmd->args, fuior_command_arg_new("enum_item",  string_type));

    fuior_command *declare_cmd_cmd = fuior_command_register(state, "declare_cmd");
    declare_cmd_cmd->vararg = fuior_command_arg_new("...", any_type);

    fuior_command *declare_var_cmd = fuior_command_register(state, "declare_var");
    fuior_list_push(&declare_var_cmd->args, fuior_command_arg_new("var_name", string_type));
    fuior_list_push(&declare_var_cmd->args, fuior_command_arg_new("var_type", string_type));

    return state;
}

bool fuior_state_has_errors(const fuior_state *state) {
    return state->errors.first != NULL;
}

void fuior_state_free(fuior_state *state) {
    free(state->intl_prefix);
    free(state->intl_namespace);
    free(state);

    // TODO: free commands

    fuior_map_clear(&state->commands, false);
    fuior_map_clear(&state->variables, false);
    fuior_map_clear(&state->named_types, false);

    for (fuior_list_item *it = state->types.first; it; it = it->next) {
        fuior_type_clear((fuior_type*)it->data);
    }
    fuior_list_clear(&state->types);
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
        fuior_analyse(state, &source_file, NULL);
    }
    if (!fuior_state_has_errors(state)) {
        fuior_generate_lua(state, &source_file);
    }

    fuior_results *results = (fuior_results *)calloc(1, sizeof(fuior_results));
    fuior_state_get_results(state, results);

    ts_tree_delete(source_file.tree);
    ts_parser_delete(parser);

    return results;
}

void fuior_state_get_results(fuior_state *state, fuior_results * results) {
    results->output = fuior_strlist_concat(&state->output);

    fuior_list_to_array(&state->errors, (void ***)&results->errors, &results->error_count);
    fuior_list_to_array(&state->warnings, (void ***)&results->warnings, &results->warning_count);

    fuior_strlist_clear(&state->output);
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

#ifdef __cplusplus
}
#endif
