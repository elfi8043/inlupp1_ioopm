#include "hash_table.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct entry entry_t;

struct entry
{
    char *key;     // holds the key
    int value;     // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    // DODGE: hard-coding number of buckets as 17.
    // NOTE: addressing this dodge is optional.
    entry_t *buckets[17];
};

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
    return calloc(1, sizeof(ioopm_hash_table_t));
}

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    free(ht);
}