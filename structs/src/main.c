#include <assert.h>

#include "heap.h"
#include "linked_list.h"
#include "vec.h"

int test_heap(void) {
  struct vec v = vec_init();
  int nums[7] = {3, 1, 8, 4, 6, 2, 7};
  for (int i = 0; i < 7; i += 1) {
    vec_push(&v, nums[i]);
  }

  vec_print(&v);

  struct heap h = heap_from_vec(v);

  heap_print(&h);

  heap_destroy(&h);

  return 0;
}

int test_list(void) {
  struct list l = list_init();

  int nums[7] = {3, 1, 8, 4, 6, 2, 7};
  for (int i = 0; i < 7; i += 1) {
    list_add(&l, nums[i]);
  }

  list_insert(&l, 3, 1);
  int elt = list_remove(&l, 2);
  assert(elt == 1);

  list_print(&l);

  list_insertion_sort(&l);
  // list_merge_sort(&l);

  list_print(&l);

  list_destroy(&l);

  return 0;
}

int test_vec(void) {
  struct vec v = vec_init();

  int nums[7] = {3, 1, 8, 4, 6, 2, 7};
  for (int i = 0; i < 7; i += 1) {
    vec_push(&v, nums[i]);
  }

  vec_print(&v);

  vec_insert(&v, 3, 1);
  int elt = vec_remove(&v, 2);
  assert(elt == 1);

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
