#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//
//     If the word is not in the hash table, put it there, and give it the value 1
//     If the word is in the hash table, Increment its current value by 1
//
// Get all hash table keys and sort according to frequency.
// For each key, in the sorted order
//
//     Print the key and its frequency
//
// Tear down the hash table, free all resources, close all files
int main(int argc, char *argv[])
{
    // Create an empty hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // For each file argument,
    for (int i = 1; i < 3; i++)
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
            char *word;
            word = strtok(result, ",.!? :;\n");
            while (word != NULL)
            {
                if (ioopm_hash_table_has_key(ht, word)) {
                    int val = 0;
                    ioopm_hash_table_lookup(ht, word, &val);
                    val += 1;
                    ioopm_hash_table_insert(ht, word, val);
                } else {
                    ioopm_hash_table_insert(ht, word, 1);
                }
                word = strtok(NULL, ",.!? :;\n");
            }

            // free(result);
        }
    }
}
