#include <assert.h>

#include "heap.h"
#include "linked_list.h"
#include "vec.h"

int test_heap(void) {
  struct heap h = heap_init();

  // TODO

  heap_destroy(&h);

  return 0;
}

int test_list(void) {
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

int test_vec(void) {
  struct vec v = vec_init();

  vec_push(&v, 1);
  vec_push(&v, 2);
  vec_push(&v, 3);
  vec_push(&v, 4);
  vec_push(&v, 6);
  vec_push(&v, 7);
  vec_push(&v, 8);

  vec_print(&v);

  vec_insert(&v, 3, 1);
  int a = vec_remove(&v, 2);
  assert(a == 2);

  vec_print(&v);

  // vec_insertion_sort(&v);
  // vec_merge_sort(&v);

  vec_print(&v);

  vec_destroy(&v);

  return 0;
}

int main(void) {
  test_heap();
  // test_list();
  // test_vec();
}
