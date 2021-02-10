#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct fuior_list_item;
typedef struct fuior_list_item {
    char * data;
    size_t length;
    struct fuior_list_item * next;
} fuior_list_item;

typedef struct {
    fuior_list_item * first;
    fuior_list_item * last;
} fuior_list;

static void fuior_list_push_nocopy_(fuior_list * list, char * data, size_t length) {
    fuior_list_item * item = (fuior_list_item*)malloc(sizeof(fuior_list_item));
    item->data = data;
    item->length = length;
    item->next = NULL;

    if (list->last) { list->last->next = item; }
    if (!list->first) { list->first = item; }
    list->last = item;
}

static inline void fuior_list_push_nocopy(fuior_list * list, char * data) {
    fuior_list_push_nocopy_(list, data, strlen(data));
}

static void fuior_list_push_(fuior_list * list, const char * data, size_t length) {
    char * buffer = (char*)malloc(length + 1);
    memcpy(buffer, data, length);
    buffer[length] = 0;
    fuior_list_push_nocopy_(list, buffer, length);
}

static inline void fuior_list_push(fuior_list * list, const char * data) {
    fuior_list_push_(list, data, strlen(data));
}

static void fuior_list_printf(fuior_list * list, const char * format, ...) {
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char * buffer = (char*)malloc(length + 1);
    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    fuior_list_push_nocopy_(list, buffer, length);
}

static void fuior_list_clear(fuior_list * list) {
    for (fuior_list_item * item = list->first; item;) {
        fuior_list_item * it = item;
        item = item->next;
        free(it->data);
        free(it);
    }
    list->first = NULL;
    list->last = NULL;
}

static void fuior_list_clear_keep_data(fuior_list * list) {
    for (fuior_list_item * item = list->first; item;) {
        fuior_list_item * it = item;
        item = item->next;
        free(it);
    }
    list->first = NULL;
    list->last = NULL;
}

static char * fuior_list_concat(fuior_list * list) {
    size_t len = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        len += item->length;
    }

    char * buffer = (char*)malloc(len + 1);
    size_t offset = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        memcpy(buffer + offset, item->data, item->length);
        offset += item->length;
    }

    buffer[len] = 0;
    return buffer;
}

static void fuior_list_to_array(fuior_list * list, char *** buffer_out, size_t * length_out) {
    size_t len = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        len += 1;
    }

    char ** buffer = (char**)malloc(len * sizeof(char*));
    size_t i = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        buffer[i] = item->data;
        i += 1;
    }

    *buffer_out = buffer;
    *length_out = len;
}
