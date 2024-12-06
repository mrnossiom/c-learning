#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vec {
  int *ptr;
  size_t len;
  size_t cap;
} vec_t;

vec_t vec_init(void);
void vec_destroy(vec_t *list);

void vec_push(vec_t *list, int elt);
int vec_pop(vec_t *list);

void vec_insert(vec_t *list, int elt, size_t index);
int vec_remove(vec_t *list, size_t index);

void vec_insertion_sort(vec_t *list);
void vec_merge_sort(vec_t *list);

#endif /* ! VEC_H */
