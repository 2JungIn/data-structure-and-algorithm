#include "../include/heap.h"
#include <stdlib.h>


const static int default_size = 15;


heap *init_heap(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    heap *h = NULL;
    if ((h = (heap *)malloc(sizeof(heap))) == NULL)   /* error: malloc() */
        return NULL;

    if ((h->v = init_vector(default_size, free_item)) == NULL)    /* error: init_vector() */
    {
        free(h);
        return NULL;
    }
    
    h->compare = compare;

    return h;
}

void destroy_heap(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return ;

    destroy_vector(h->v);
    free(h);
}

void print_heap(const heap *h, void (*print_func)(const void *))
{
    print_vector(h->v, print_func);
}


void heapify(heap *h, const int i, const int size)
{
    if (h == NULL)   /* error: invalid arg */
        return ;
    
    if (i < 0 || i >= heap_size(h))  /* error: heap out of range */
        return ;
    
    if (size < 0 || size > heap_size(h)) /* error: heap out of range */
        return ;
    
    int left = 2*i + 1;
    int right = 2*i + 2;

    int change_idx = i;

    int (*compare)(const void *, const void *) = h->compare;

    if (left < size && compare(vector_get_at(h->v, left), vector_get_at(h->v, change_idx)) > 0)
        change_idx = left;
    if (right < size && compare(vector_get_at(h->v, right), vector_get_at(h->v, change_idx)) > 0)
        change_idx = right;

    if (change_idx != i)
    {
        vector_swap(h->v, i, change_idx);
        heapify(h, change_idx, size);
    }
}

void bulid_heap(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return ;

    int size = heap_size(h);
    for (int i = (size / 2) - 1; i >= 0; i--)
        heapify(h, i, size);
}

void heap_sort(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return ;
    
    bulid_heap(h);
    for (int i = heap_size(h) - 1; i > 0; i--)
    {
        vector_swap(h->v, 0, i);
        heapify(h, 0, i);
    }
}


int heap_empty(const heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return -1;
    
    return vector_empty(h->v);
}

int heap_size(const heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return -1;
    
    return vector_size(h->v);
}

void heap_clear(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return ;
    
    vector_clear(h->v);
}


void *heap_front(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return NULL;
    
    return vector_get_at(h->v, 0);
}

void heap_push(heap *h, void *item)
{
    if (h == NULL)   /* error: invalid arg */
        return ;
    
    if (item == NULL)    /* error: invalid arg */
        return ;

    vector_push_back(h->v, item);
    bulid_heap(h);
}

void *heap_pop(heap *h)
{
    if (h == NULL)   /* error: invalid arg */
        return NULL;

    void *ret_item = NULL;

    vector_swap(h->v, 0, heap_size(h) - 1);
    ret_item = vector_pop_back(h->v);
    heapify(h, 0, heap_size(h));

    return ret_item;
}
