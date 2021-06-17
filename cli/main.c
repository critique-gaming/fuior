#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <libgen.h>

#include "fuior.h"

static char *copy_string(const char *str) {
    if (!str) return NULL;
    char *s = (char*)malloc(strlen(str) + 1);
    strcpy(s, str);
    return s;
}

static char *path_dirname(const char *path, size_t extra_space) {
    char *path_copy = copy_string(path);
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
    char *intl_filename;
    char *import_root;
    char *source_filename;
    FILE *source_file_handle;
    char *header_filename;
    FILE *header_file_handle;
    char *out_filename;
    FILE *out_file_handle;
    bool error_ranges;
    bool emit_code;
} command_line;

static void print_help(FILE *stream) {
    fprintf(stream, "usage: fuior [options] source_file\n");
    fprintf(stream, "\tsource_file\tSource file name. Use - for stdin\n");
    fprintf(stream, "\t--output out_filename\tFile name where to emit lua code. Use - for stdout. Defaults to stdout\n");
    fprintf(stream, "\t--o out_filename\n");
    fprintf(stream, "\t--no-emit\tDon't emit code. Just check for errors\n");
    fprintf(stream, "\t--header header_filename\tPath to a header with definitions. Defaults to searching for a config.fui in parent directories\n");
    fprintf(stream, "\t--intl-filename\tFilename used to emit the default intl prefix. Defaults to the source file's filename\n");
    fprintf(stream, "\t--import-root\tImport paths are relative to this. Defaults to the source file's directory\n");
    fprintf(stream, "\t--error-ranges\tShow full error ranges\n");
}

static FILE *assert_fopen(const char *filename, const char *mode) {
    FILE *handle = fopen(filename, mode);
    if (!handle) {
        fprintf(stderr, "Error opening %s: ", filename);
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
    cli->emit_code = true;

    for (int i = 1, expected = 0; i < argc; i += 1 + expected) {
        expected = 0;
        const char *arg = argv[i];
        if (0 == strcmp(arg, "--output") || 0 == strcmp(arg, "-o")) {
            expect_args(1);
            if (cli->out_filename) { help_and_exit(); }
            cli->out_filename = copy_string(argv[i + 1]);

        } else if (0 == strcmp(arg, "--intl-filename")) {
            expect_args(1);
            cli->intl_filename = copy_string(argv[i + 1]);

        } else if (0 == strcmp(arg, "--import-root")) {
            expect_args(1);
            cli->import_root = copy_string(argv[i + 1]);

        } else if (0 == strcmp(arg, "--no-emit") || 0 == strcmp(arg, "--no-generate")) {
            cli->emit_code = false;

        } else if (0 == strcmp(arg, "--error-ranges")) {
            cli->error_ranges = true;

        } else if (0 == strcmp(arg, "--header")) {
            expect_args(1);
            cli->header_filename = copy_string(argv[i + 1]);

        } else if (0 == strcmp(arg, "--help") || 0 == strcmp(arg, "-h")) {
            print_help(stdout);
            exit(0);

        } else {
            if (cli->source_filename) { help_and_exit(); }
            cli->source_filename = copy_string(argv[i]);

        }
    }

    if (!cli->out_filename || 0 == strcmp(cli->out_filename, "-")) {
        free(cli->out_filename);
        cli->out_filename = copy_string("stdout");
        cli->out_file_handle = stdout;
    } else {
        cli->out_file_handle = assert_fopen(cli->out_filename, "w");
    }

    if (!cli->source_filename) { help_and_exit(); }
    if (0 == strcmp(cli->source_filename, "-")) {
        free(cli->source_filename);
        cli->source_filename = copy_string("stdin");
        cli->source_file_handle = stdin;
        if (!cli->import_root) {
            cli->import_root = getcwd(NULL, 0);
        }
    } else {
        cli->source_file_handle = assert_fopen(cli->source_filename, "rb");
        if (!cli->header_filename) {
            char *fname;
            cli->header_file_handle = open_config(cli->source_filename, &fname);
            cli->header_filename = fname;
        }
        if (!cli->import_root) {
            cli->import_root = path_dirname(cli->source_filename, 0);
        }
    }

    if (cli->header_filename && !cli->header_file_handle) {
        cli->header_file_handle = assert_fopen(cli->header_filename, "rb");
    }
}

static void command_line_free(command_line *cli) {
    free(cli->intl_filename);
    free(cli->import_root);
    free(cli->source_filename);
    free(cli->header_filename);
    free(cli->out_filename);
}

static void print_message(FILE *stream, const fuior_message *msg, command_line *cli) {
    if (cli->error_ranges) {
        fprintf(stream, "%s:%u:%u-%u:%u %s\n", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->end_row + 1, msg->end_column + 1, msg->message);
    } else {
        fprintf(stream, "%s:%u:%u %s\n", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
    }
}

typedef struct import_callback_context {
    fuior_source_file **source_files;
    size_t source_file_count;
    size_t source_file_capacity;
    command_line *cli;
    TSParser *parser;
} import_callback_context;

static char * on_import(const char * import_name, fuior_state * state, void * context) {
    import_callback_context *ctx = (import_callback_context*)context;

    size_t n = strlen(ctx->cli->import_root);
    size_t m = strlen(PATH_SEP);
    size_t o = strlen(import_name);
    char * path = (char*)malloc(n + m + o + 1);
    strcpy(path, ctx->cli->import_root);
    strcpy(path + n, PATH_SEP);
    strcpy(path + n + m, import_name);

    FILE *handle = fopen(path, "rb");
    if (!handle) {
        size_t n = snprintf(NULL, 0, "Cannot open %s", path);
        char * errstring = (char*)malloc(n + 1);
        snprintf(errstring, n + 1, "Cannot open %s", path);
        free(path);
        return errstring;
    }

    for (size_t i = 0; i < ctx->source_file_count; i ++) {
        const char * fname = ctx->source_files[i]->filename;
        if (fname && 0 == strcmp(path, fname)) {
            free(path);
            return NULL;
        }
    }

    if (ctx->source_file_count >= ctx->source_file_capacity) {
        ctx->source_file_capacity *= 2;
        ctx->source_files = (fuior_source_file**)realloc(
            ctx->source_files,
            sizeof(fuior_source_file) * ctx->source_file_capacity
        );
    }

    fuior_source_file *source_file = (fuior_source_file*)calloc(1, sizeof(fuior_source_file));
    ctx->source_files[ctx->source_file_count++] = source_file;
    size_t file_len;
    char *contents = read_file(handle, &file_len);
    fuior_parse(source_file, ctx->parser, contents, file_len, path, NULL);
    fuior_check_syntax(state, source_file);
    fuior_lint(state, source_file, &on_import, context);

    return NULL;
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

    fuior_source_file *source_file = (fuior_source_file*)calloc(1, sizeof(fuior_source_file));
    fuior_source_file *header_file = (fuior_source_file*)calloc(1, sizeof(fuior_source_file));

    import_callback_context ctx;
    ctx.parser = parser;
    ctx.cli = &cli;
    ctx.source_files = malloc(sizeof (fuior_source_file*) * 2);
    ctx.source_file_capacity = 2;
    ctx.source_file_count = 2;
    ctx.source_files[0] = source_file;
    ctx.source_files[1] = header_file;

    fuior_parse(header_file, parser, header_contents, header_len, copy_string(cli.header_filename), NULL);
    fuior_parse(source_file, parser, file_contents, file_len, copy_string(cli.source_filename), NULL);

    fuior_state *state = fuior_state_new();

    fuior_check_syntax(state, header_file);
    fuior_check_syntax(state, source_file);
    if (!fuior_state_has_errors(state)) {
        fuior_analyse(state, header_file, cli.intl_filename);
        fuior_analyse(state, source_file, cli.intl_filename);
        fuior_lint(state, header_file, &on_import, &ctx);
        fuior_lint(state, source_file, &on_import, &ctx);
    }
    if (!fuior_state_has_errors(state) && cli.emit_code) {
        fuior_emit_lua(state, source_file);
    }

    fuior_results *results = (fuior_results *)calloc(1, sizeof(fuior_results));
    fuior_state_get_results(state, results);

    for (size_t i = 0; i < ctx.source_file_count; i++) {
        ts_tree_delete(ctx.source_files[i]->tree);
    }
    ts_parser_delete(parser);

    for (size_t i = 0; i < results->warning_count; i++) {
        fprintf(stderr, "WARNING: ");
        print_message(stderr, results->warnings[i], &cli);
    }

    for (size_t i = 0; i < results->error_count; i++) {
        fprintf(stderr, "ERROR: ");
        print_message(stderr, results->errors[i], &cli);
    }

    int return_code = -1;
    if (results->output && results->error_count == 0) {
        printf("%s", results->output);
        return_code = 0;
    }

    fuior_results_free(results);
    command_line_free(&cli);
    for (size_t i = 0; i < ctx.source_file_count; i++) {
        free((char*)ctx.source_files[i]->input);
        free((char*)ctx.source_files[i]->filename);
        free(ctx.source_files[i]);
    }
    free(ctx.source_files);
    return return_code;
}
