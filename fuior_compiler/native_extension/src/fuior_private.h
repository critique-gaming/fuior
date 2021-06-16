#ifndef FUIOR_PRIVATE_H
#define FUIOR_PRIVATE_H

#include <tree_sitter/api.h>
#include "fuior.h"
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
    struct fuior_type *character_enum;
    struct fuior_type *type_any;
    struct fuior_type *type_nil;
    struct fuior_type *type_string;
    struct fuior_type *type_number;
    struct fuior_type *type_boolean;
};

typedef enum fuior_type_tag {
    TYPE_NIL,
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_STRING_LITERAL,
    TYPE_BOOLEAN,
    TYPE_ENUM,
    TYPE_ANY,
    TYPE_UNION,
    TYPE_INTERSECTION,
} fuior_type_tag;

typedef struct fuior_type {
    fuior_type_tag tag;
    char *name;
    union {
        struct {
            fuior_map items;
        } as_enum;
        struct {
            fuior_list items;
        } as_op;
        struct {
            char *literal;
        } as_string_literal;
    };
} fuior_type;

typedef struct fuior_command_arg {
    fuior_type *type;
    char *name;
} fuior_command_arg;

static inline char *fuior_clone_string(const char *s) {
    char *copy = (char*)malloc(strlen(s) + 1);
    strcpy(copy, s);
    return copy;
}

static inline char *fuior_node_to_string_(fuior_state *state, TSNode node, size_t start_offset, size_t end_offset) {
    size_t start = ts_node_start_byte(node) + start_offset;
    size_t end = ts_node_end_byte(node) - end_offset;
    char * res = (char*)malloc(end - start + 1);
    memcpy(res, state->input + start, end - start);
    res[end - start] = 0;
    return res;
}

#define fuior_node_to_string(state, node) fuior_node_to_string_(state, node, 0, 0)
#define fuior_string_node_to_string(state, node) fuior_node_to_string_(state, node, 1, 1)

static inline fuior_command_arg *fuior_command_arg_new(const char *name, fuior_type *type) {
    fuior_command_arg *arg = (fuior_command_arg*)malloc(sizeof(fuior_command_arg));
    arg->type = type;
    arg->name = fuior_clone_string(name);
    return arg;
}

typedef struct fuior_command {
    fuior_list args;
    fuior_command_arg *vararg;
} fuior_command;

void fuior_command_clear(fuior_command *self);

fuior_type *fuior_type_new(fuior_state *state, fuior_type_tag tag);
void fuior_type_clear(fuior_type *type);
char *fuior_type_name(fuior_type *type);

typedef struct fuior_tree_sitter_symbols_t {
    TSSymbol ERROR;
    TSSymbol comment;
    TSSymbol command_statement;
    TSSymbol command_verb;
    TSSymbol command_arg;
    TSSymbol bare_word;
    TSSymbol number;
    TSSymbol string;
    TSSymbol intl_string;
    TSSymbol boolean;
    TSSymbol identifier;
    TSSymbol type_identifier;
    TSSymbol function_call;
    TSSymbol unary_expression;
    TSSymbol binary_expression;
    TSSymbol paran_expression;
    TSSymbol choose_statement;
    TSSymbol choice;
    TSSymbol choice_condition;
    TSSymbol choice_meta;
    TSSymbol block;
    TSSymbol text_copy;
    TSSymbol text_statement;
    TSSymbol text_actor;
    TSSymbol text_animation;
    TSSymbol assign_statement;
    TSSymbol assign_lvalue;
    TSSymbol assign_operator;
    TSSymbol assign_rvalue;
    TSSymbol if_statement;
    TSSymbol condition;
    TSSymbol if_clause;
    TSSymbol elseif_clause;
    TSSymbol else_clause;
    TSSymbol arg_definition;
    TSSymbol arg_type;
    TSSymbol arg_name;
    TSSymbol arg_definition_list;
    TSSymbol command_signature;
    TSSymbol command_name;
    TSSymbol return_type;
    TSSymbol define_command_statement;
    TSSymbol declare_command_statement;
    TSSymbol arg_list;
    TSSymbol declare_var_decorator;
    TSSymbol decorator_name;
    TSSymbol declare_var_statement;
    TSSymbol var_name;
    TSSymbol var_type;
    TSSymbol var_default_value;
    TSSymbol return_statement;
    TSSymbol return_value;
} fuior_tree_sitter_symbols_t;

extern fuior_tree_sitter_symbols_t fuior_tree_sitter_symbols;
#define sym fuior_tree_sitter_symbols

typedef struct fuior_tree_sitter_fields_t {
    TSFieldId actor;
    TSFieldId animation;
    TSFieldId arg_list;
    TSFieldId arguments;
    TSFieldId block;
    TSFieldId body;
    TSFieldId condition;
    TSFieldId copy;
    TSFieldId default_value;
    TSFieldId lvalue;
    TSFieldId meta;
    TSFieldId name;
    TSFieldId operator_;
    TSFieldId return_type;
    TSFieldId return_value;
    TSFieldId rvalue;
    TSFieldId signature;
    TSFieldId type;
    TSFieldId verb;
} fuior_tree_sitter_fields_t;

extern fuior_tree_sitter_fields_t fuior_tree_sitter_fields;
#define fld fuior_tree_sitter_fields

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

static inline TSNode fuior_skip_comments(TSNode node) {
    TSSymbol symbol = ts_node_symbol(node);
    while (symbol == sym.comment) {
        node = ts_node_next_named_sibling(node);
        symbol = ts_node_symbol(node);
    }
    return node;
}

#endif
