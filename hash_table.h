#pragma once
#include <stddef.h>
#include "common.h"
#include <stdbool.h>

/**
 * @file hash_table.h
 * @author write both your names here
 * @date write the date you started working on this
 * @brief Simple hash table that maps string keys to integer values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 */

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by the key and boolean true if key removed, else false e.g key nonexistent
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, elem_t *result);

/// @brief check if hash table ht has certain key
/// @param ht hash table operated upon
/// @param key key to check
/// @return true if ht has key else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key);

/// @brief check if hash table ht is empty
/// @param ht hash table operated upon
/// @return true if ht is empty else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief check size of a hash table ht
/// @param ht hash table operated upon
/// @return size of the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

size_t ioopm_hash_int(int value);

/// @brief compares if two elem_t are bools
/// @param a first variable to compare
/// @param b second variable to compare
/// @return true if a and b are both bools
bool ioopm_bool_comp(elem_t a, elem_t b);

/// @brief compares if two elem_t are strings
/// @param a first variable to compare
/// @param b second variable to compare
/// @return true if a and b are both strings
bool ioopm_string_comp(elem_t a, elem_t b);

/// @brief compares if two elem_t are ints
/// @param a first variable to compare
/// @param b second variable to compare
/// @return true if a and b are both ints
bool ioopm_int_comp(elem_t a, elem_t b);

/// @brief compares if two elem_t are floats
/// @param a first variable to compare
/// @param b second variable to compare
/// @return true if a and b are both floats
bool ioopm_float_comp(elem_t a, elem_t b);
