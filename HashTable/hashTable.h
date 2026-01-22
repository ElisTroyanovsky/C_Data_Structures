#ifndef HashTable_H
#define HashTable_H

#include <stddef.h>

    typedef struct HashTable HashTable;

    // Create a new hash table with initial capacity (will be rounded up).
    // Returns NULL on allocation failure.
    HashTable* ht_create(size_t initial_capacity);

    // Free the table and all stored keys.
    void ht_destroy(HashTable* ht);

    // Insert or update key -> value.
    // Returns 1 on success, 0 on allocation failure.
    int ht_put(HashTable* ht, const char* key, int value);

    // Get value by key.
    // Returns 1 if found (writes to out_value), 0 if not found.
    int ht_get(const HashTable* ht, const char* key, int* out_value);

    // Remove key from the table.
    // Returns 1 if removed, 0 if not found.
    int ht_remove(HashTable* ht, const char* key);

    // Check if key exists.
    int ht_contains(const HashTable* ht, const char* key);

    // Number of stored entries.
    size_t ht_size(const HashTable* ht);

    // Current bucket count (capacity).
    size_t ht_capacity(const HashTable* ht);

#endif