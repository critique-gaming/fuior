#ifndef FUIOR_STRLIST_H
#define FUIOR_STRLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

struct fuior_strlist_item;
typedef struct fuior_strlist_item {
    struct fuior_strlist_item * next;
    char * data;
    size_t length;
} fuior_strlist_item;

typedef struct {
    fuior_strlist_item * first;
    fuior_strlist_item * last;
} fuior_strlist;

#define fuior_strlist_init(list) memset(list, 0, sizeof(fuior_strlist))

static void fuior_strlist_push_nocopy_(fuior_strlist * list, char * data, size_t length) {
    fuior_strlist_item * item = (fuior_strlist_item*)malloc(sizeof(fuior_strlist_item));
    item->data = data;
    item->length = length;
    item->next = NULL;

    if (list->last) { list->last->next = item; }
    if (!list->first) { list->first = item; }
    list->last = item;
}

static inline void fuior_strlist_push_nocopy(fuior_strlist * list, char * data) {
    fuior_strlist_push_nocopy_(list, data, strlen(data));
}

static void fuior_strlist_push_(fuior_strlist * list, const char * data, size_t length) {
    char * buffer = (char*)malloc(length + 1);
    memcpy(buffer, data, length);
    buffer[length] = 0;
    fuior_strlist_push_nocopy_(list, buffer, length);
}

static inline void fuior_strlist_push(fuior_strlist * list, const char * data) {
    fuior_strlist_push_(list, data, strlen(data));
}

static void fuior_strlist_printf(fuior_strlist * list, const char * format, ...) {
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char * buffer = (char*)malloc(length + 1);
    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    fuior_strlist_push_nocopy_(list, buffer, length);
}

static void fuior_strlist_clear(fuior_strlist * list) {
    for (fuior_strlist_item * item = list->first; item;) {
        fuior_strlist_item * it = item;
        item = item->next;
        free(it->data);
        free(it);
    }
    list->first = NULL;
    list->last = NULL;
}

static void fuior_strlist_clear_keep_data(fuior_strlist * list) {
    for (fuior_strlist_item * item = list->first; item;) {
        fuior_strlist_item * it = item;
        item = item->next;
        free(it);
    }
    list->first = NULL;
    list->last = NULL;
}

static char * fuior_strlist_concat(fuior_strlist * list) {
    size_t len = 0;
    for (fuior_strlist_item * item = list->first; item; item = item->next) {
        len += item->length;
    }

    char * buffer = (char*)malloc(len + 1);
    size_t offset = 0;
    for (fuior_strlist_item * item = list->first; item; item = item->next) {
        memcpy(buffer + offset, item->data, item->length);
        offset += item->length;
    }

    buffer[len] = 0;
    return buffer;
}

static void fuior_strlist_to_array(fuior_strlist * list, char *** buffer_out, size_t * length_out) {
    size_t len = 0;
    for (fuior_strlist_item * item = list->first; item; item = item->next) {
        len += 1;
    }

    char ** buffer = (char**)malloc(len * sizeof(char*));
    size_t i = 0;
    for (fuior_strlist_item * item = list->first; item; item = item->next) {
        buffer[i] = item->data;
        i += 1;
    }

    *buffer_out = buffer;
    *length_out = len;
}

#endif
