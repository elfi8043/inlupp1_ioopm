#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//
//     If the word is not in the hash table, put it there, and give it the frequency 1
//     If the word is in the hash table, Increment its current frequency by 1
//
// Get all hash table keys and sort according to frequency.
// For each key, in the sorted order
//
//     Print the key and its frequency
//
// Tear down the hash table, free all resources, close all files

typedef struct word word_t;

struct word
{
    char *key;     // holds the key
    int frequency; // holds the frequency
};

// char *file_to_string(char *file_name) {

//}

int compare_frequency(const void *word1, const void *word2)
{
    const word_t *w1 = word1;
    const word_t *w2 = word2;

    return w1->frequency - w2->frequency;
}

void insert_file_words_ht(char *filename, ioopm_hash_table_t *ht)
{
    FILE *in = fopen(filename, "r");
    char *result = NULL;
    size_t size = 0;
    ssize_t nread;
    // read each word in the file
    while ((nread = getline(&result, &size, in)) != -1)
    {
        char *token = strtok(result, ",.:!? \n");
        while (token != NULL)
        {
            // check if word in ht
            if (ioopm_hash_table_has_key(ht, token))
            {
                // increase value by 1
                int val = -1;
                ioopm_hash_table_lookup(ht, token, &val);
                val++;
                ioopm_hash_table_insert(ht, strdup(token), val);
            }
            else
            {
                // insert
                ioopm_hash_table_insert(ht, strdup(token), 1);
            }
            token = strtok(NULL, ",.:!? \n");
        }
    }

    free(result);
    fclose(in);
}

int main(int argc, char *argv[])
{
    // Create an empty hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // For each file argument,
    for (int i = 1; i < argc; i++)
    {
        insert_file_words_ht(argv[i], ht);
    }

    // Flatten ht into array
    int ht_size = ioopm_hash_table_size(ht);

    word_t words[ht_size];

    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
    for (int i = 0; i < ht_size; i++)
    {
        char *curr_word = ioopm_hash_table_iterator_current_key(it);
        int curr_frequency = ioopm_hash_table_iterator_current_value(it);
        word_t word_to_insert = {.key = curr_word, .frequency = curr_frequency};
        words[i] = word_to_insert;
        ioopm_hash_table_iterator_advance(it);
    }

    // Sort the words in array according to their frequencies
    qsort(words, ht_size, sizeof(word_t), compare_frequency);

    // print sorted array
    for (int j = 0; j < ht_size; j++)
    {
        printf("%s: %d\n", words[j].key, words[j].frequency);
    }
    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy(ht);
}
