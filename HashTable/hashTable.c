#include "hashTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;
} Entry;

struct HashTable {
    Entry** buckets;
    size_t capacity;
    size_t size;
};

static size_t next_pow2(size_t x) {
    if (x < 8) return 8;
    size_t p = 1;
    while (p < x) p <<= 1;
    return p;
}

static uint64_t hash_str(const char* s) {
    uint64_t h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++)) {
        h = ((h << 5) + h) + c;
    }
    return h;
}

static char* str_dup(const char* s) {
    size_t n = strlen(s);
    char* copy = (char*)malloc(n + 1);
    if (!copy) return NULL;
    memcpy(copy, s, n + 1);
    return copy;
}

static Entry* entry_find(Entry* head, const char* key) {
    for (Entry* e = head; e; e = e->next) {
        if (strcmp(e->key, key) == 0) return e;
    }
    return NULL;
}

static void entry_list_free(Entry* head) {
    while (head) {
        Entry* next = head->next;
        free(head->key);
        free(head);
        head = next;
    }
}

static int ht_rehash(HashTable* ht, size_t new_cap) {
    Entry** new_buckets = (Entry**)calloc(new_cap, sizeof(Entry*));
    if (!new_buckets) return 0;

    for (size_t i = 0; i < ht->capacity; i++) {
        Entry* e = ht->buckets[i];
        while (e) {
            Entry* next = e->next;

            uint64_t h = hash_str(e->key);
            size_t idx = (size_t)(h & (new_cap - 1));
            e->next = new_buckets[idx];
            new_buckets[idx] = e;

            e = next;
        }
    }

    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_cap;
    return 1;
}

static int ht_maybe_grow(HashTable* ht) {
    if (ht->size * 4 < ht->capacity * 3) return 1;
    return ht_rehash(ht, ht->capacity * 2);
}



HashTable* ht_create(size_t initial_capacity) {
    HashTable* ht = (HashTable*)calloc(1, sizeof(HashTable));
    if (!ht) return NULL;

    ht->capacity = next_pow2(initial_capacity);
    ht->buckets = (Entry**)calloc(ht->capacity, sizeof(Entry*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    ht->size = 0;
    return ht;
}

void ht_destroy(HashTable* ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->capacity; i++) {
        entry_list_free(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

int ht_put(HashTable* ht, const char* key, int value) {
    if (!ht || !key) return 0;

    if (!ht_maybe_grow(ht)) return 0;

    uint64_t h = hash_str(key);
    size_t idx = (size_t)(h & (ht->capacity - 1));

    Entry* found = entry_find(ht->buckets[idx], key);
    if (found) {
        found->value = value;
        return 1;
    }

    Entry* e = (Entry*)malloc(sizeof(*e));
    if (!e) return 0;

    e->key = str_dup(key);
    if (!e->key) {
        free(e);
        return 0;
    }

    e->value = value;
    e->next = ht->buckets[idx];
    ht->buckets[idx] = e;
    ht->size++;
    return 1;
}

int ht_get(const HashTable* ht, const char* key, int* out_value) {
    if (!ht || !key) return 0;

    uint64_t h = hash_str(key);
    size_t idx = (size_t)(h & (ht->capacity - 1));

    Entry* found = entry_find(ht->buckets[idx], key);
    if (!found) return 0;

    if (out_value) *out_value = found->value;
    return 1;
}

int ht_contains(const HashTable* ht, const char* key) {
    return ht_get(ht, key, NULL);
}

int ht_remove(HashTable* ht, const char* key) {
    if (!ht || !key) return 0;

    uint64_t h = hash_str(key);
    size_t idx = (size_t)(h & (ht->capacity - 1));

    Entry* prev = NULL;
    Entry* cur = ht->buckets[idx];

    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            if (prev) prev->next = cur->next;
            else ht->buckets[idx] = cur->next;

            free(cur->key);
            free(cur);
            ht->size--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

size_t ht_size(const HashTable* ht) {
    return ht ? ht->size : 0;
}

size_t ht_capacity(const HashTable* ht) {
    return ht ? ht->capacity : 0;
}