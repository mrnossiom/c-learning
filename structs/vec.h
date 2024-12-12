#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

struct vec {
  int *ptr;
  size_t len;
  size_t cap;
};

struct vec vec_init(void);
void vec_destroy(struct vec *list);

void vec_push(struct vec *list, int elt);
int vec_pop(struct vec *list);

void vec_insert(struct vec *list, int elt, size_t index);
int vec_remove(struct vec *list, size_t index);

void vec_insertion_sort(struct vec *list);
void vec_merge_sort(struct vec *list);

#endif /* ! VEC_H */
