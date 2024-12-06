#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct list
{
    size_t len;
    node_t *head;
} list_t;

list_t list_init(void);
void list_destroy(list_t *list);

void list_add(list_t *list, int elt);
int list_pop(list_t *list);

void list_insert(list_t *list, int elt, size_t index);
int list_remove(list_t *list, size_t index);

void list_insertion_sort(list_t *list);
void list_merge_sort(list_t *list);

#endif /* ! LINKED_LIST_H */
