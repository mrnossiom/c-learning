#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

#include "vec.h"

struct heap
{
  struct vec buffer;
};

void heap_print(struct heap *heap);

struct heap heap_init(void);
void heap_destroy(struct heap *heap);

struct heap heap_from_vec(struct vec vec);
struct vec heap_to_vec(struct heap heap);

void heap_heapify(struct heap *heap, size_t size, size_t root);

int heap_push(struct heap *heap);
int heap_pop(struct heap *heap);

#endif /* ! HEAP_H */
