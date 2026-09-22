#include "hash_table.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct entry entry_t;

#define No_buckets 17

struct entry
{
    char *key;     // holds the key
    int value;     // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    // DODGE: hard-coding number of buckets as No_buckets.
    // NOTE: addressing this dodge is optional.
    entry_t buckets[No_buckets];
};

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    return calloc(1, sizeof(ioopm_hash_table_t));
}

// static void destroy_linked_list(entry_t *curr)
//{
//     if (curr == NULL)
//     {
//         return;
//     }
//     else
//     {
//         entry_t *new_curr = curr->next; // new current
//         free(curr);
//         return destroy_linked_list(new_curr);
//     }
// }

static void destroy_linked_list(entry_t *curr)
{
    while (curr != NULL)
    {
        entry_t *new_curr = curr->next; // new current
        free(curr);
        curr = new_curr;
    }
}

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < No_buckets; i++)
    {
        entry_t *curr_list = ht->buckets[i].next;
        if (curr_list == NULL)
        {
            continue;
        }
        else
        {
            destroy_linked_list(curr_list);
        }
    }
    free(ht);
}

static size_t string_knr_hash(const char *str)
{
    size_t result = 0;
    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char)*str);
        str++;
    }
    return result;
}

static entry_t *entry_create(char *key, int value, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));
    entry->key = key;
    entry->value = value;
    entry->next = next;
    return entry;
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
    size_t bucket = string_knr_hash(key) % No_buckets;
    entry_t *list = &ht->buckets[bucket];
    while (list->next != NULL)
    {
        if (strcmp(list->next->key, key) == 0)
        {
            break;
        }
        list = list->next;
    }
    // Either we are at the end of the list or at the previous node
    return list;
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result)
{
    entry_t *previous = find_previous_entry(ht, key);

    if (previous->next == NULL)
    {
        return false;
    }
    if (strcmp(previous->next->key, key) == 0)
    {
        *result = previous->next->value;
        if (previous->next->next == NULL)
        {
            entry_t *temp = previous->next;
            previous->next = NULL;
            free(temp);
        }
        else
        {
            entry_t *temp = previous->next;
            previous->next = previous->next->next;
            free(temp);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
    // find previous entry, or the last entry if the key does not exist
    entry_t *previous = find_previous_entry(ht, key);

    // if the key exists, update the value, otherwise create a new entry
    if (previous->next != NULL)
    {
        previous->next->value = value;
    }
    else
    {
        previous->next = entry_create(key, value, NULL);
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
    entry_t *previous = find_previous_entry(ht, key);

    if (previous->next == NULL)
    {
        return false;
    }
    if (strcmp(previous->next->key, key) == 0)
    {
        *result = previous->next->value;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key)
{
    int result = -1;
    return ioopm_hash_table_lookup(ht, key, &result);
}

static int size_linked_list(entry_t *curr)
{
    int sum = 0;
    while (curr != NULL)
    {
        entry_t *new_curr = curr->next; // new current
        sum += 1;
        curr = new_curr;
    }
    return sum;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    int sum = 0;
    for (int i = 0; i < No_buckets; i++)
    {
        // Returns No nodes of linked list
        sum += size_linked_list(ht->buckets[i].next);
    }
    return sum;
}