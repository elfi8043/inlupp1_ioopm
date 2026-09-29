#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "list_iterator.h"
#include <assert.h>

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

//////////////////////////////////////////////
//////////// ITERATOR
//////////////////////////////////////////////

struct list_iterator
{
    ioopm_list_t *list;
    node_t *current_node;
    int curr_index;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    iter->list = l;
    iter->current_node = l->first;
    return iter;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    return (iter->current_node->next = NULL);
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    assert(iter->current_node->next != NULL && "AT END");
    iter->current_node = iter->current_node->next;
    iter->curr_index += 1;
}

int ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current_node->val;
}

/// NOTE: REMOVE IS OPTIONAL TO IMPLEMENT
/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
int ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    int val = ioopm_list_remove(iter->list, iter->curr_index);
    iter->curr_index -= 1;
    return val;
}

/// NOTE: INSERT IS OPTIONAL TO IMPLEMENT
/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
    ioopm_list_insert(iter->list, iter->curr_index, element);
    iter->curr_index += 1;
}