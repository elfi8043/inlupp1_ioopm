#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

typedef struct node node_t;

struct node
{
    int val;
    node_t *next;
};

struct list
{
    node_t *first;
    node_t *last;
    int size;
};

ioopm_list_t *ioopm_list_create(void) {
    return calloc(1, sizeof(ioopm_list_t));
}

static node_t *node_create(int value, node_t *next) {
    node_t *node = calloc(1, sizeof(node_t));
    node->val = value;
    node->next = next;
    return node;
}

void ioopm_list_destroy(ioopm_list_t *list) {
    node_t *curr = list->first;
    while (curr != NULL)
    {
        node_t *new_curr = curr->next;
        free(curr);
        curr = new_curr;
    }
}

int main(void) {
    return 0;
}