#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include <libgen.h>

#include "fuior.h"

static char *path_dirname(const char *path, size_t extra_space) {
    size_t n = strlen(path);
    char *path_copy = (char*)malloc(n + 1);
    strncpy(path_copy, path, n + 1);

    const char *dn = dirname(path_copy);
    size_t m = strlen(dn);
    char *dn_copy = (char*)malloc(m + extra_space + 1);
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
        char *out = (char*)malloc(n + strlen(CONFIG_SUFFIX) + 1);
        strcpy(out, dir);
        *out_path = out;
    }

    return fin;
}

static char * read_file(FILE *fin, size_t *len) {
    if (fseek(fin, 0, SEEK_END) == 0) {
        size_t fin_len = ftell(fin);
        fseek(fin, 0, SEEK_SET);

        char * buffer = (char*)malloc(fin_len);
        fread(buffer, 1, fin_len, fin);
        fclose(fin);

        *len = fin_len;
        return buffer;
    }

    size_t capacity = 512;
    size_t length = 0;
    char * buffer = (char*)malloc(capacity);

    while (true) {
        if (length == capacity) {
            capacity = capacity * 2;
            buffer = (char*)realloc(buffer, capacity);
        }
        size_t to_read = capacity - length;
        size_t read_bytes = fread(buffer + length, 1, to_read, fin);
        length += read_bytes;
        if (read_bytes < to_read) {
            break;
        }
    }

    if (ferror(fin)) {
        fprintf(stderr, "Read error\n");
        exit(-1);
    }

    *len = length;
    return buffer;
}

typedef struct {
    const char *intl_filename;
    const char *source_filename;
    FILE *source_file_handle;
    const char *header_filename;
    FILE *header_file_handle;
    const char *out_filename;
    FILE *out_file_handle;
    bool error_ranges;
    bool generate_code;
} command_line;

static void print_help(FILE *stream) {
    fprintf(stream, "usage: fuior [options] source_file\n");
    fprintf(stream, "\tsource_file\tSource file name. Use - for stdin\n");
    fprintf(stream, "\t--output out_filename\tFile name where to generate lua code. Use - for stdout. Defaults to stdout\n");
    fprintf(stream, "\t--o out_filename\n");
    fprintf(stream, "\t--no-generate\tDon't generate code. Just check for errors\n");
    fprintf(stream, "\t--header header_filename\tPath to a header with definitions. Defaults to searching for a config.fui in parent directories\n");
    fprintf(stream, "\t--intl-filename\tFilename used to generate the default intl prefix. Defaults to the source file's filename\n");
    fprintf(stream, "\t--error-ranges\tShow full error ranges\n");
}

static FILE *assert_fopen(const char *filename, const char *mode) {
    FILE *handle = fopen(filename, mode);
    if (!handle) {
        fprintf(stderr, "Error opening %s", filename);
        perror("open()");
        exit(-1);
    }
    return handle;
}

static void parse_command_line(command_line *cli, int argc, char **argv) {
    memset(cli, 0, sizeof(command_line));

    #define help_and_exit() do { print_help(stderr); exit(-1); } while(0)
    #define expect_args(n) if (i + (n) >= argc) { help_and_exit(); }; expected = (n)

    cli->error_ranges = false;
    cli->generate_code = true;

    for (int i = 1, expected = 0; i < argc; i += 1 + expected) {
        expected = 0;
        const char *arg = argv[i];
        if (0 == strcmp(arg, "--output") || 0 == strcmp(arg, "-o")) {
            expect_args(1);
            if (cli->out_filename) { help_and_exit(); }
            cli->out_filename = argv[i + 1];

        } else if (0 == strcmp(arg, "--intl-filename")) {
            expect_args(1);
            cli->intl_filename = argv[i + 1];

        } else if (0 == strcmp(arg, "--no-generate")) {
            cli->generate_code = false;

        } else if (0 == strcmp(arg, "--error-ranges")) {
            cli->error_ranges = true;

        } else if (0 == strcmp(arg, "--header")) {
            expect_args(1);
            cli->header_filename = argv[i + 1];

        } else if (0 == strcmp(arg, "--help") || 0 == strcmp(arg, "-h")) {
            print_help(stdout);
            exit(0);

        } else {
            if (cli->source_filename) { help_and_exit(); }
            cli->source_filename = argv[i];

        }
    }

    if (!cli->out_filename || 0 == strcmp(cli->out_filename, "-")) {
        cli->out_filename = "stdout";
        cli->out_file_handle = stdout;
    } else {
        cli->out_file_handle = assert_fopen(cli->out_filename, "w");
    }

    if (!cli->source_filename) { help_and_exit(); }
    if (0 == strcmp(cli->source_filename, "-")) {
        cli->source_filename = "stdin";
        cli->source_file_handle = stdin;
    } else {
        cli->source_file_handle = assert_fopen(cli->source_filename, "rb");
        if (!cli->header_filename) {
            char *fname;
            cli->header_file_handle = open_config(cli->source_filename, &fname);
            cli->header_filename = fname;
        }
    }

    if (cli->header_filename && !cli->header_file_handle) {
        cli->header_file_handle = assert_fopen(cli->header_filename, "rb");
    }
}

static void print_message(FILE *stream, const fuior_message *msg, command_line *cli) {
    if (cli->error_ranges) {
        fprintf(stream, "%s:%u:%u-%u:%u %s\n", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->end_row + 1, msg->end_column + 1, msg->message);
    } else {
        fprintf(stream, "%s:%u:%u %s\n", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
    }
}

int main(int argc, char ** argv) {
    command_line cli;
    parse_command_line(&cli, argc, argv);

    if (cli.header_file_handle != NULL && strcmp(cli.header_filename, cli.source_filename) == 0) { // Maybe we want to compile the actual config
        fclose(cli.header_file_handle);
        cli.header_file_handle = NULL;
    }

    size_t header_len = 0;
    char *header_contents = cli.header_file_handle != NULL ? read_file(cli.header_file_handle, &header_len) : NULL;

    size_t file_len;
    char *file_contents = read_file(cli.source_file_handle, &file_len);

    TSParser *parser = fuior_parser_new();

    fuior_source_file source_file, header_file;
    fuior_parse(&header_file, parser, header_contents, header_len, cli.header_filename, NULL);
    fuior_parse(&source_file, parser, file_contents, file_len, cli.source_filename, NULL);

    fuior_state *state = fuior_state_new();

    fuior_check_syntax(state, &header_file);
    fuior_check_syntax(state, &source_file);
    if (!fuior_state_has_errors(state)) {
        fuior_analyse(state, &header_file, cli.intl_filename);
        fuior_analyse(state, &source_file, cli.intl_filename);
        fuior_lint(state, &header_file);
        fuior_lint(state, &source_file);
    }
    if (!fuior_state_has_errors(state) && cli.generate_code) {
        fuior_generate_lua(state, &source_file);
    }

    fuior_results *results = (fuior_results *)calloc(1, sizeof(fuior_results));
    fuior_state_get_results(state, results);

    ts_tree_delete(header_file.tree);
    ts_tree_delete(source_file.tree);
    ts_parser_delete(parser);

    for (size_t i = 0; i < results->warning_count; i++) {
        fprintf(stderr, "WARNING: ");
        print_message(stderr, results->warnings[i], &cli);
    }

    for (size_t i = 0; i < results->error_count; i++) {
        fprintf(stderr, "ERROR: ");
        print_message(stderr, results->errors[i], &cli);
    }

    if (results->output && results->error_count == 0) {
        printf("%s", results->output);
        fuior_results_free(results);
        free(file_contents);
        return 0;
    }

    fuior_results_free(results);
    free(file_contents);
    return -1;
}
