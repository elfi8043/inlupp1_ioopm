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

ioopm_list_t *ioopm_list_create(void)
{
    return calloc(1, sizeof(ioopm_list_t));
}

static node_t *node_create(int value, node_t *next)
{
    node_t *node = calloc(1, sizeof(node_t));
    node->val = value;
    node->next = next;
    return node;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    node_t *curr = list->first;
    while (curr != NULL)
    {
        node_t *new_curr = curr->next;
        free(curr);
        curr = new_curr;
    }
    free(list);
}

static void empty_insert(ioopm_list_t *list, int value)
{
    node_t *node = node_create(value, NULL);
    list->first = node;
    list->last = node;
    list->size += 1;
}

void ioopm_list_prepend(ioopm_list_t *list, int value)
{
    if (list->size == 0)
    {
        empty_insert(list, value);
    }
    else
    {
        node_t *node = node_create(value, list->first);
        list->first = node;
        list->size += 1;
    }
}

void ioopm_list_append(ioopm_list_t *list, int value)
{
    if (list->size == 0)
    {
        empty_insert(list, value);
    }
    else
    {
        node_t *node = node_create(value, NULL);
        list->last->next = node;
        list->last = node;
        list->size += 1;
    }
}

int ioopm_list_head(ioopm_list_t *list)
{
    return list->first->val;
}

int ioopm_list_last(ioopm_list_t *list)
{
    return list->last->val;
}

static node_t *find_previous_node(ioopm_list_t *list, int index)
{
    int count = 0;
    node_t *curr = list->first;
    while (count < (index - 1))
    {
        curr = curr->next;
        count += 1;
    }
    return curr;
}

int ioopm_list_remove(ioopm_list_t *list, int index)
{
    if (list->size == 0)
    {
        puts("EMPTY LIST");
        return -99;
    }
    if (list->size == 1)
    {
        free(list->first);
    }
    int val = -1;
    node_t *prev = find_previous_node(list, index);
    val = prev->next->val;
    node_t *temp = prev->next;
    prev->next = temp->next;
    free(temp);
    list->size -= 1;
    return val;
}

void ioopm_list_insert(ioopm_list_t *list, int index, int value)
{
    node_t *prev = find_previous_node(list, index);
    if (list->size == 0)
    {
        empty_insert(list, value);
    }
    else
    {
        prev->next = node_create(value, prev->next);
    }
    list->size += 1;
}

int ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return (list->first == NULL);
}

int ioopm_list_get(ioopm_list_t *list, int index)
{
    if (list->size == 0)
    {
        puts("EMPTY LIST");
        return -99;
    }
    if (index == 0)
    {
        return list->first->val;
    }
    node_t *prev = find_previous_node(list, index);
    return prev->next->val;
}