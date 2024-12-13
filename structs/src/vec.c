#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

void vec_print(struct vec *v) {
  size_t index = 0;

  putchar('[');
  while (v->len - index != 0) {
    printf(" %d", v->ptr[index]);
    index++;
  }
  puts(" ]");
}

struct vec vec_init(void) {
  size_t len = 0;
  size_t cap = 4;

  int *ptr = malloc(cap * sizeof(int));
  if (ptr == NULL)
    errx(1, "memory exhausted");

  struct vec v = {ptr, len, cap};
  return v;
}

void vec_destroy(struct vec *v) { free(v->ptr); }

void _vec_grow(struct vec *v) {
  v->cap *= 2;

  int *ptr = realloc(v->ptr, v->cap * sizeof(int));
  if (ptr == NULL)
    errx(1, "memory exhausted");

  v->ptr = ptr;
}

void vec_push(struct vec *v, int elt) {
  if (v->len == v->cap)
    _vec_grow(v);

  v->ptr[v->len] = elt;
  v->len += 1;
}

int vec_pop(struct vec *v) {
  assert(v->len != 0 && "v must be a non-empty vec");

  // shrink length
  v->len -= 1;

  return v->ptr[v->len];
}

void vec_insert(struct vec *v, int elt, size_t index) {
  assert(index <= v->len && "index must be in bounds");

  // grow if needed
  if (v->len == v->cap)
    _vec_grow(v);

  // copy cells from last to first to avoid overlapping
  for (size_t i = v->len; i > index; i -= 1) {
    v->ptr[i] = v->ptr[i - 1];
  }

  v->ptr[index] = elt;
  v->len += 1;
}

int vec_remove(struct vec *v, size_t index) {
  assert(v->len != 0 && "v must be a non-empty vec");
  assert(index < v->len && "index must be in bounds");

  // retrieve removed value
  int ret = v->ptr[index];

  v->len -= 1;

  // shift cells left from first to last to avoid overlapping
  for (size_t i = index; i < v->len; i += 1) {
    v->ptr[i] = v->ptr[i + 1];
  }

  return ret;
}

void vec_insertion_sort(struct vec *v);
void vec_merge_sort(struct vec *v);
