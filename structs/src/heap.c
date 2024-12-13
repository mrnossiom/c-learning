#include <assert.h>

#include "heap.h"
#include "vec.h"

void heap_print(struct heap *heap) { vec_print(&heap->buffer); }

struct heap heap_init(void) {
  struct vec buffer = vec_init();
  struct heap heap = {
      .buffer = buffer,
  };
  return heap;
}

void heap_destroy(struct heap *heap) { vec_destroy(&heap->buffer); }

struct heap heap_from_vec(struct vec vec) {
  struct heap heap = {
      .buffer = vec,
  };

  heap_heapify(&heap, heap.buffer.len, 0);

  return heap;
}

struct vec heap_to_vec(struct heap heap) { return heap.buffer; }

void heap_heapify(struct heap *heap, size_t size, size_t root) {
  assert(heap->buffer.len != 0);
  struct vec *buffer = &heap->buffer;

  for (;;) {
    size_t smallest = root;
    size_t left = 2 * smallest + 1;
    size_t right = 2 * smallest + 2;

    if (left < size && vec_get(buffer, left) < vec_get(buffer, root)) {
      smallest = left;
    } else {
      smallest = root;
    }

    if (right < size && vec_get(buffer, right) < vec_get(buffer, smallest)) {
      smallest = right;
    }

    if (smallest == root)
      break;

    int tmp = vec_get(buffer, smallest);
    *vec_get_ptr(buffer, smallest) = vec_get(buffer, root);
    *vec_get_ptr(buffer, root) = tmp;

    root = smallest;
  }
}
