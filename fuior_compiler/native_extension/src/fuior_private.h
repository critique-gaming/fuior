#ifndef FUIOR_PRIVATE_H
#define FUIOR_PRIVATE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <tree_sitter/api.h>
#include "fuior_list.h"
#include "fuior_map.h"
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

    fuior_map commands;
    fuior_map named_types;
    fuior_map variables;
    fuior_list types;

    struct fuior_type *varname_enum;
};

typedef enum fuior_type_tag {
    TYPE_NIL,
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_ENUM,
    TYPE_ANY,
    TYPE_UNION,
    TYPE_INTERSECTION,
} fuior_type_tag;

typedef struct fuior_type {
    fuior_type_tag tag;
    union {
        struct {
            fuior_map items;
        } as_enum;
        struct {
            fuior_list items;
        } as_op;
    };
} fuior_type;

typedef struct fuior_command_arg {
    fuior_type *type;
    char *name;
    char *type_name;
} fuior_command_arg;

static inline fuior_command_arg *fuior_command_arg_new(char *name, char *type_name, fuior_type *type) {
    fuior_command_arg *arg = (fuior_command_arg*)malloc(sizeof(fuior_command_arg));
    arg->type = type;
    arg->name = (char*)malloc(strlen(name) + 1);
    strcpy(arg->name, name);
    arg->type_name = (char*)malloc(strlen(type_name) + 1);
    strcpy(arg->type_name, type_name);
    return arg;
}

typedef struct fuior_command {
    fuior_list args;
    fuior_command_arg *vararg;
} fuior_command;

static inline fuior_type *fuior_type_new(fuior_state *state, fuior_type_tag tag) {
    fuior_type *type = (fuior_type*)calloc(1, sizeof(fuior_type));
    type->tag = tag;
    fuior_list_push(&state->types, (void*)type);
    return type;
}

static inline void fuior_type_clear(fuior_type *type) {
    if (type->tag == TYPE_ENUM) {
        fuior_map_clear(&type->as_enum.items, false);
    } else if (type->tag == TYPE_UNION || type->tag == TYPE_INTERSECTION) {
        fuior_list_clear_keep_data(&type->as_op.items);
    }
}

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

extern const char * const fuior_special_commands_intl[];
int fuior_get_special_command(fuior_state * state, TSNode command_verb, const char * const *special_commands);
char * fuior_command_arg_to_string(fuior_state *state, TSNode node);

fuior_command *fuior_command_register(fuior_state *state, const char *name);

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
