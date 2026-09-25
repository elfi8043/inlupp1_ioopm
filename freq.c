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
    int frequency;     // holds the frequency
};

//char *file_to_string(char *file_name) {

//}

int main(int argc, char *argv[])
{
    // Create an empty hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // For each file argument,
    for (int i = 1; i < argc; i++)
    {
        char *filename = argv[i];
        puts("hello");
        FILE *in = fopen(filename, "r");
        puts("goodbye");
        char *result = NULL;
        size_t size = 0;
        ssize_t nread;

        // read each word in the file
        while ((nread = getline(&result, &size, in)) != -1)
        {
            // printf("Retrieved line of length %zd:\n", nread);
            // fwrite(result, nread, 1, stdout);
            word_t word;
            word.key = strtok(result, ",.!? :;\n");
            while (word.key != NULL)
            {
                if (ioopm_hash_table_has_key(ht, word.key)) {
                    word.frequency = 0;
                    ioopm_hash_table_lookup(ht, word.key, &word.frequency);
                    word.frequency += 1;
                    ioopm_hash_table_insert(ht, word.key, word.frequency);
                } else {
                    ioopm_hash_table_insert(ht, word.key, 1);
                }
                word.key = strtok(NULL, ",.!? :;\n");
            }

            // free(result);
        }

        int ht_size = ioopm_hash_table_size(ht);

        word_t words[ht_size];

        ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create;
        for (int i = 0; i < ht_size; i++) {
            char *curr_word = ioopm_hash_table_iterator_current_key(it);
            int curr_frequency = ioopm_hash_table_iterator_current_value(it);
            words[i] = {.word = curr_word, .frequency = curr_frequency};
        }
    }
}
