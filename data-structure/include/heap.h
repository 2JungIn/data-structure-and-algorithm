#ifndef _HEAP_H_
#define _HEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vector.h"

typedef struct heap
{
    vector *v;
    int (*compare)(const void *, const void *);
} heap;

heap *init_heap(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_heap(heap *h);
void print_heap(const heap *h, void (*print_func)(const void *));


void heapify(heap *h, const int i, const int size);
void bulid_heap(heap *h);
void heap_sort(heap *h);

int heap_empty(const heap *h);
int heap_size(const heap *h);
void heap_clear(heap *h);

void *heap_front(heap *h);
void heap_push(heap *h, void *item);
void *heap_pop(heap *h);

#ifdef __cplusplus
}
#endif

#endif  /* _HEAP_H_ */