#include "linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void list_print(list_t *list) {
  node_t *head = list->head;

  putchar('[');
  while (head) {
    printf(" %d", head->data);
    head = head->next;
  }
  puts(" ]");
}

list_t list_init(void) {
  list_t list = {0, NULL};
  return list;
}

void list_destroy(list_t *list) {
  node_t *current = list->head;

  // visit each node to free them
  while (current != NULL) {
    node_t *next = current->next;
    free(current);
    current = next;
  }
}

void list_add(list_t *list, int elt) {
  node_t **current = &list->head;

  // get to the end of the linked list
  while (*current != NULL) {
    current = &((*current)->next);
  }

  node_t *ptr = malloc(sizeof(node_t));
  assert(ptr != NULL);

  // create new node and assign to new memory cell
  node_t new = {elt, NULL};
  *ptr = new;

  // point current node to new memory cell
  *current = ptr;

  list->len += 1;
}

int list_pop(list_t *list) {
  assert(list->len != 0 && "list must not be empty");

  node_t **current = &list->head;

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

void list_insert(list_t *list, int elt, size_t index) {
  assert(index < list->len && "index must be in bounds");

  node_t *current = list->head;

  // get to nth node
  while (--index) {
    current = current->next;
  }

  node_t *ptr = malloc(sizeof(node_t));
  assert(ptr != NULL);

  // create new node and point to next
  node_t new = {elt, current->next};
  *ptr = new;

  // point current node to new node
  current->next = ptr;

  list->len += 1;
}

int list_remove(list_t *list, size_t index) {
  assert(index < list->len && "index must be in bounds");

  node_t *current = list->head;

  // get to nth node
  while (--index) {
    current = current->next;
  }

  // store next node
  node_t *next = current->next->next;

  // store removed node data
  int ret = current->next->data;

  // free removed node
  free(current->next);

  // point current node to next
  current->next = next;

  list->len -= 1;

  return ret;
}

node_t *_list_insert_sorted(node_t *sorted, node_t *elem) {
  node_t *first = sorted;
  node_t *previous = NULL;

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

void list_insertion_sort(list_t *list) {
  node_t *current = list->head;
  node_t *sorted = NULL;

  while (current != NULL) {
    node_t *next = current->next;
    list_print(list);
    list->head = _list_insert_sorted(sorted, current);
    sorted = list->head;
    current = next;
  }
}

// oui oui aller
void list_merge_sort(list_t *list) { return; }

int main(void) {
  list_t l = list_init();

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
