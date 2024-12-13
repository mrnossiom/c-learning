#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

struct vec {
  int *ptr;
  size_t len;
  size_t cap;
};

void vec_print(struct vec *v);

struct vec vec_init(void);
void vec_destroy(struct vec *v);

void vec_push(struct vec *v, int elt);
int vec_pop(struct vec *v);

int vec_get(struct vec *v, size_t index);
int *vec_get_ptr(struct vec *v, size_t index);

void vec_insert(struct vec *v, int elt, size_t index);
int vec_remove(struct vec *v, size_t index);

void vec_insertion_sort(struct vec *v);
void vec_merge_sort(struct vec *v);

#endif /* ! VEC_H */
