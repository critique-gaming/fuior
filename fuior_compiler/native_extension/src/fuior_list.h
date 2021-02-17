#ifndef FUIOR_LIST_H
#define FUIOR_LIST_H

#include <stdlib.h>
#include <stdbool.h>

struct fuior_list_item;
typedef struct fuior_list_item {
    struct fuior_list_item * next;
    void *data;
} fuior_list_item;

typedef struct {
    fuior_list_item * first;
    fuior_list_item * last;
} fuior_list;

static void fuior_list_push(fuior_list * list, void * data) {
    fuior_list_item * item = (fuior_list_item*)malloc(sizeof(fuior_list_item));
    item->data = data;
    item->next = NULL;

    if (list->last) { list->last->next = item; }
    if (!list->first) { list->first = item; }
    list->last = item;
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

static void fuior_list_to_array(fuior_list * list, void *** buffer_out, size_t * length_out) {
    size_t len = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        len += 1;
    }

    void ** buffer = (void**)malloc(len * sizeof(void*));
    size_t i = 0;
    for (fuior_list_item * item = list->first; item; item = item->next) {
        buffer[i] = item->data;
        i += 1;
    }

    *buffer_out = buffer;
    *length_out = len;
}

#endif
