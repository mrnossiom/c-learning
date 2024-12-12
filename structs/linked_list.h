#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *next;
};

struct list
{
    size_t len;
    struct node *head;
};

struct list list_init(void);
void list_destroy(struct list *list);

void list_add(struct list *list, int elt);
int list_pop(struct list *list);

void list_insert(struct list *list, int elt, size_t index);
int list_remove(struct list *list, size_t index);

void list_insertion_sort(struct list *list);
void list_merge_sort(struct list *list);

#endif /* ! LINKED_LIST_H */
