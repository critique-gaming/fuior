#ifndef FUIOR_MAP_H
#define FUIOR_MAP_H

#include <stdlib.h>
#include <string.h>

#define FUIOR_MAP_HASH_BITS 8
#define FUIOR_MAP_HASH_ROTATE_BITS 3
#define FUIOR_MAP_BUCKET_COUNT (1 << FUIOR_MAP_HASH_BITS)

typedef struct fuior_map_item {
    char *key;
    void *value;
    struct fuior_map_item *next;
} fuior_map_item;

typedef struct fuior_map {
    fuior_map_item *buckets[FUIOR_MAP_BUCKET_COUNT];
} fuior_map;

static inline size_t fuior_map_hash(const char *key) {
    size_t hash = 0;
    for (const char *c = key; *c; c += 1) {
        // Circular bit rotate then XOR character
        hash = (((hash << FUIOR_MAP_HASH_ROTATE_BITS) | (hash >> (FUIOR_MAP_HASH_BITS - FUIOR_MAP_HASH_ROTATE_BITS))) ^ (*c)) & ((1 << FUIOR_MAP_HASH_BITS) - 1);
    }
    return hash & ((1 << FUIOR_MAP_HASH_BITS) - 1);
}

#define fuior_map_init(self) memset((self), 0, sizeof(fuior_map));

static inline void fuior_map_clear(fuior_map *self, bool free_values) {
    for (int i = 0; i < FUIOR_MAP_BUCKET_COUNT; i++) {
        while (self->buckets[i]) {
            fuior_map_item *item = self->buckets[i];
            self->buckets[i] = item->next;
            free(item->key);
            if (free_values) free(item->value);
        }
    }
}

static inline void fuior_map_set(fuior_map *self, const char *key, void *value) {
    size_t hash = fuior_map_hash(key);
    fuior_map_item *item;

    item = self->buckets[hash];
    while (item != NULL && 0 != strcmp(item->key, key)) {
        item = item->next;
    }

    if (item == NULL) {
        item = (fuior_map_item*)malloc(sizeof(fuior_map_item));
        item->next = self->buckets[hash];
        self->buckets[hash] = item;
        item->key = (char*)malloc(strlen(key) + 1);
        strcpy(item->key, key);
    }

    item->value = value;
}

static inline void *fuior_map_get(fuior_map *self, const char *key) {
    size_t hash = fuior_map_hash(key);
    fuior_map_item *item = self->buckets[hash];
    while (item != NULL && 0 != strcmp(item->key, key)) {
        item = item->next;
    }
    return item ? item->value : NULL;
};

#endif
