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
extern "C"
#endif

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
        size_t dirname_count = basename - filename;
        char *normalized_dirname = malloc(dirname_count + 2);
        normalized_dirname[0] = '/';
        strncpy(normalized_dirname + 1, filename, dirname_count);
        normalized_dirname[dirname_count + 1] = '\0';

        for (size_t j = 1; j <= dirname_count; j++) {
            if (normalized_dirname[j] == '\\') {
                normalized_dirname[j] = '/';
            }
        }

        uint32_t dirname_hash;
        if (normalized_dirname[1] == '/') {
            dirname_hash = hash(normalized_dirname + 1, dirname_count);
        } else {
            dirname_hash = hash(normalized_dirname, 1 + dirname_count);
        }
        free(normalized_dirname);

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

static char * command_arg_to_string(fuior_state *state, TSNode node) {
    while (1) {
        if (ts_node_is_null(node)) { return NULL; }
        if (ts_node_symbol(node) == sym.command_arg) { break; }
        node = ts_node_next_named_sibling(node);
    }

    TSNode child = ts_node_named_child(node, 0);
    TSSymbol symbol = ts_node_symbol(child);
    while (symbol == sym.comment) {
        child = ts_node_next_named_sibling(child);
        symbol = ts_node_symbol(child);
    }

    size_t start = 0;
    size_t end = 0;
    if (symbol == sym.bare_word) {
        start = ts_node_start_byte(child);
        end = ts_node_end_byte(child);
    } else if (symbol == sym.string) {
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
    if (ts_node_symbol(node) == sym.command_verb) {
        int cmd = fuior_get_special_command(state, node);
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

void fuior_analyse(fuior_state *state, fuior_source_file *source_file, const char *intl_filename) {
    state->filename = source_file->filename;
    state->input = source_file->input;
    scan_for_special_commands(state, ts_tree_root_node(source_file->tree));
    if (!state->intl_prefix) {
        state->intl_prefix = default_intl_prefix(intl_filename ? intl_filename : source_file->filename);
    }
}
