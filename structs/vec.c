#include "linked_list.h"
#include "vec.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void vec_print(vec_t *v) {
  size_t index = 0;

  putchar('[');
  while (v->len - index != 0) {
    printf(" %d", v->ptr[index]);
    index++;
  }
  puts(" ]");
}

vec_t vec_init(void) {
  size_t len = 0;
  size_t cap = 4;

  int *ptr = malloc(cap * sizeof(int));
  assert(ptr != NULL);

  vec_t v = {ptr, len, cap};
  return v;
}

void vec_destroy(vec_t *v) { free(v->ptr); }

void _vec_grow(vec_t *v) {
  size_t new_cap = v->cap * 2;

  int *ptr = malloc(new_cap * sizeof(int));
  assert(ptr != NULL);

  // copy old buffer to new buffer
  memcpy(ptr, v->ptr, v->len * sizeof(int));

  // free old buffer
  free(v->ptr);

  v->ptr = ptr;
  v->cap = new_cap;
}

void vec_push(vec_t *v, int elt) {
  if (v->len == v->cap)
    _vec_grow(v);

  v->ptr[v->len] = elt;
  v->len += 1;
}

int vec_pop(vec_t *v) {
  assert(v->len != 0 && "v must be a non-empty vec");

  // shrink length
  v->len -= 1;

  return v->ptr[v->len];
}

void vec_insert(vec_t *v, int elt, size_t index) {
  assert(index < v->len && "index must be in bounds");

  // grow if needed
  if (v->len == v->cap)
    _vec_grow(v);

  // copy cells from last to first
  for (size_t i = v->len; i > index; i -= 1) {
    memcpy(&v->ptr[i], &v->ptr[i - 1], sizeof(int));
  }

  v->ptr[index] = elt;
  v->len += 1;
}

int vec_remove(vec_t *v, size_t index) {
  assert(v->len != 0 && "v must be a non-empty vec");
  assert(index < v->len && "index must be in bounds");

  // retrieve removed value
  int ret = v->ptr[index];

  v->len -= 1;

  // shift cells left
  for (size_t i = index; i < v->len; i += 1) {
    memcpy(&v->ptr[i], &v->ptr[i + 1], sizeof(int));
  }

  return ret;
}

void vec_insertion_sort(vec_t *v);
void vec_merge_sort(vec_t *v);

int main(void) {
  vec_t v = vec_init();

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
