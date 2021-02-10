#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#include <libgen.h>

#include "fuior.h"

static char *path_dirname(const char *path, size_t extra_space) {
    size_t n = strlen(path);
    char *path_copy = malloc(n + 1);
    strncpy(path_copy, path, n + 1);

    const char *dn = dirname(path_copy);
    size_t m = strlen(dn);
    char *dn_copy = malloc(m + extra_space + 1);
    strncpy(dn_copy, dn, m + extra_space + 1);

    free(path_copy);
    return dn_copy;
}

#define PATH_SEP "/"
#define CONFIG_SUFFIX PATH_SEP "config.fui"

FILE *open_config(const char *path, char **out_path) {
    char *dir = path_dirname(path, strlen(CONFIG_SUFFIX));

    if (strcmp(path, dir) == 0) { // Reached FS root
        free(dir);
        *out_path = NULL;
        return NULL;
    }

    size_t n = strlen(dir);
    strcat(dir, CONFIG_SUFFIX);

    FILE *fin = fopen(dir, "rb");
    if (!fin) {
        dir[n] = '\0';
        fin = open_config(dir, out_path);
        free(dir);
    } else {
        *out_path = malloc(n + strlen(CONFIG_SUFFIX) + 1);
        strcpy(*out_path, dir);
    }

    return fin;
}

char * read_file(FILE *fin, size_t *len) {
    size_t fin_len;
    fseek(fin, 0, SEEK_END);
    fin_len = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    char * buffer = malloc(fin_len);
    fread(buffer, 1, fin_len, fin);
    fclose(fin);

    *len = fin_len;
    return buffer;
}

int main(int argc, char ** argv) {
    assert(argc >= 2);

    const char *filename = argv[1];

    FILE * fin = fopen(filename, "rb");
    if (!fin) {
        perror("Cannot open file");
        return -1;
    }

    const char *error_filename = argc >= 3 ? argv[2] : argv[1];

    size_t file_len;
    char *file_contents = read_file(fin, &file_len);

    char *config_path;
    FILE *fconfig = open_config(filename, &config_path);
    if (fconfig != NULL && strcmp(config_path, filename) == 0) { // Maybe we want to compile the actual config
        fclose(fconfig);
        fconfig = NULL;
    }

    size_t config_len = 0;
    char *config_contents = fconfig != NULL ? read_file(fconfig, &config_len) : NULL;

    TSParser *parser = fuior_parser_new();

    fuior_source_file source_file, config_file;
    fuior_parse(&config_file, parser, config_contents, config_len, config_path, NULL);
    fuior_parse(&source_file, parser, file_contents, file_len, error_filename, NULL);

    fuior_state *state = fuior_state_new();

    fuior_check_syntax(state, &config_file);
    fuior_check_syntax(state, &source_file);
    if (!fuior_state_has_errors(state)) {
        fuior_analyse(state, &config_file);
        fuior_analyse(state, &source_file);
        fuior_lint(state, &config_file);
        fuior_lint(state, &source_file);
    }
    if (!fuior_state_has_errors(state)) {
        fuior_generate(state, &source_file);
    }

    fuior_results *results = (fuior_results *)calloc(1, sizeof(fuior_results));
    fuior_state_get_results(state, results);

    ts_tree_delete(config_file.tree);
    ts_tree_delete(source_file.tree);
    ts_parser_delete(parser);

    for (size_t i = 0; i < results->warning_count; i++) {
        printf("WARNING: %s\n", results->warnings[i]);
    }

    for (size_t i = 0; i < results->error_count; i++) {
        printf("ERROR: %s\n", results->errors[i]);
    }

    if (results->output) {
        printf("%s", results->output);
        fuior_results_free(results);
        free(file_contents);
        return 0;
    }

    fuior_results_free(results);
    free(file_contents);
    return -1;
}
