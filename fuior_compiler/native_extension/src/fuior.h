#ifndef FUIOR_H
#define FUIOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <tree_sitter/api.h>

struct fuior_state;
typedef struct fuior_state fuior_state;

typedef struct {
    char * output;
    size_t error_count;
    char ** errors;
    size_t warning_count;
    char ** warnings;
} fuior_results;

typedef struct {
    const char *input;
    size_t input_len;
    const char *filename;
    TSTree *tree;
} fuior_source_file;

TSParser *fuior_parser_new();
void fuior_parse(fuior_source_file *source_file, TSParser *parser, const char * input, size_t input_len, const char * filename, TSTree *previous_tree);

fuior_state *fuior_state_new();
void fuior_state_get_results(fuior_state *state, fuior_results * results);
bool fuior_state_has_errors(const fuior_state *state);
void fuior_state_free(fuior_state *state);

void fuior_check_syntax(fuior_state *state, fuior_source_file *source_file);
void fuior_analyse(fuior_state *state, fuior_source_file *source_file);
void fuior_lint(fuior_state *state, fuior_source_file *source_file);
void fuior_generate(fuior_state *state, fuior_source_file *source_file);

void fuior_results_free(fuior_results * results);

fuior_results *fuior_compile(const char * input, size_t input_len, const char * filename);

#ifdef __cplusplus
}
#endif
#endif
