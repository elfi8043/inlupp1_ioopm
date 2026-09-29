#include "linked_list.h"
typedef struct node node_t;

struct node
{
    void *val;
    node_t *next;
};

struct list
{
    node_t *first;
    node_t *last;
    int size;
};

static void destroy_linked_list(ioopm_list_t *list)
{
    node_t curr = list->first;
    while (curr != NULL)
    {
        node_t *new_curr = curr->next;
        free(curr);
        curr = new_curr;
    }
}

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @pre 0 <= index <= length(list)
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted
void ioopm_list_insert(ioopm_list_t *list, int index, int value)
{
    if (index == 0)
    {
        ioopm_list_append(list, value);
    }
    else if (index == list->size)
    {
        ioopm_list_prepend(list, value);
    }
    else
    {
        int count = 0;
        node_t *curr = list->first;
        while (count < index)
        {
            count += 1;
            curr = curr->next;
        }
        // insert
        curr->next = node_create(value, curr->next);
    }
}