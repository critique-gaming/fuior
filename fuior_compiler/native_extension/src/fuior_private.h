#ifndef FUIOR_PRIVATE_H
#define FUIOR_PRIVATE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <tree_sitter/api.h>
#include "fuior_list.h"
#include "fuior_strlist.h"

struct fuior_state {
    const char * input;
    fuior_strlist output;

    const char * filename;
    char * intl_namespace;
    char * intl_prefix;
    unsigned indent;

    fuior_list errors;
    fuior_list warnings;
};

typedef struct fuior_tree_sitter_symbols_t {
    TSSymbol ERROR;
    TSSymbol comment;
    TSSymbol command;
    TSSymbol command_verb;
    TSSymbol command_arg;
    TSSymbol bare_word;
    TSSymbol number;
    TSSymbol string;
    TSSymbol boolean;
    TSSymbol identifier;
    TSSymbol unary_expression;
    TSSymbol binary_expression;
    TSSymbol paran_expression;
    TSSymbol choose_statement;
    TSSymbol choice;
    TSSymbol choice_condition;
    TSSymbol block;
    TSSymbol text_copy;
    TSSymbol show_text;
    TSSymbol text_actor;
    TSSymbol text_animation;
    TSSymbol stat_operation;
    TSSymbol stat_lvalue;
    TSSymbol stat_operator;
    TSSymbol stat_rvalue;
    TSSymbol if_statement;
    TSSymbol condition;
    TSSymbol if_clause;
    TSSymbol elseif_clause;
    TSSymbol else_clause;
} fuior_tree_sitter_symbols_t;

extern fuior_tree_sitter_symbols_t fuior_tree_sitter_symbols;
#define sym fuior_tree_sitter_symbols

#define CMD_INTL_NAMESPACE 0
#define CMD_INTL_PREFIX 1
#define CMD_COUNT 2

extern const char * const fuior_special_commands[];
int fuior_get_special_command(fuior_state * state, TSNode command_verb);

fuior_message *fuior_message_create(const char *filename, TSNode node, const char *format, ...);

#define add_error(node, ...) fuior_list_push(&state->errors, (void*)fuior_message_create(state->filename, node, __VA_ARGS__))
#define add_warning(node, ...) fuior_list_push(&state->warnings, (void*)fuior_message_create(state->filename, node, __VA_ARGS__))

static inline uint32_t hash(const char * data, size_t length) {
    uint32_t hashAddress = 0;
    for (size_t i = 0; i < length; i++){
        hashAddress = data[i] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
    return hashAddress;
}

#ifdef __cplusplus
}
#endif
#endif
