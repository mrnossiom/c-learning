#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void list_print(struct list *list) {
  struct node *head = list->head;

  putchar('[');
  while (head) {
    printf(" %d", head->data);
    head = head->next;
  }
  puts(" ]");
}

struct list list_init(void) {
  struct list list = {0, NULL};
  return list;
}

void list_destroy(struct list *list) {
  struct node *current = list->head;

  // visit each node to free them
  while (current != NULL) {
    struct node *next = current->next;
    free(current);
    current = next;
  }
}

void list_add(struct list *list, int elt) {
  struct node **current = &list->head;

  // get to the end of the linked list
  while (*current != NULL) {
    current = &((*current)->next);
  }

  struct node *ptr = malloc(sizeof(struct node));
  if (ptr == NULL)
    errx(1, "memory exhausted");

  // create new node and assign to new memory cell
  struct node new = {elt, NULL};
  *ptr = new;

  // point current node to new memory cell
  *current = ptr;

  list->len += 1;
}

int list_pop(struct list *list) {
  assert(list->len != 0 && "list must not be empty");

  struct node **current = &list->head;

  // point second to last
  while (*current != NULL && (*current)->next != NULL) {
    current = &((*current)->next);
  }

  // get associated data
  int ret = (*current)->data;

  // free memory and clear second to last node
  free(*current);
  *current = NULL;

  list->len -= 1;

  return ret;
}

void list_insert(struct list *list, int elt, size_t index) {
  assert(index <= list->len && "index must be in bounds");

  struct node *current = list->head;

  // get to nth node
  while (--index) {
    current = current->next;
  }

  struct node *ptr = malloc(sizeof(struct node));
  if (ptr == NULL)
    errx(1, "memory exhausted");

  // create new node and point to next
  struct node new = {elt, current->next};
  *ptr = new;

  // point current node to new node
  current->next = ptr;

  list->len += 1;
}

int list_remove(struct list *list, size_t index) {
  assert(index < list->len && "index must be in bounds");

  struct node *current = list->head;

  // get to nth node
  while (--index) {
    current = current->next;
  }

  // store next node
  struct node *next = current->next->next;

  // store removed node data
  int ret = current->next->data;

  // free removed node
  free(current->next);

  // point current node to next
  current->next = next;

  list->len -= 1;

  return ret;
}

struct node *_list_insert_sorted(struct node *sorted, struct node *elem) {
  struct node *first = sorted;
  struct node *previous = NULL;

  while (sorted != NULL && sorted->data < elem->data) {
    previous = sorted;
    sorted = sorted->next;
  }

  elem->next = sorted;

  if (previous == NULL) {
    first = elem;
  } else {
    previous->next = elem;
  }

  return first;
}

void list_insertion_sort(struct list *list) {
  struct node *current = list->head;
  struct node *sorted = NULL;

  while (current != NULL) {
    struct node *next = current->next;
    list_print(list);
    list->head = _list_insert_sorted(sorted, current);
    sorted = list->head;
    current = next;
  }
}

// oui oui aller
void list_merge_sort(struct list *list) { return; }

int main(void) {
  struct list l = list_init();

  list_add(&l, 1);
  list_add(&l, 2);
  list_add(&l, 7);
  list_add(&l, 6);
  list_add(&l, 8);
  list_add(&l, 4);
  list_add(&l, 8);
  list_add(&l, 3);

  list_insert(&l, 3, 1);
  int a = list_remove(&l, 2);
  assert(a == 2);

  list_print(&l);

  list_insertion_sort(&l);
  // list_merge_sort(&l);

  list_print(&l);

  list_destroy(&l);

  return 0;
}
