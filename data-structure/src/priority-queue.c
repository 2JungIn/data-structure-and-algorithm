#include "../include/priority-queue.h"

priority_queue *init_priority_queue(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    return init_heap(free_item, compare);
}

void destroy_priority_queue(priority_queue *pq)
{
    destroy_heap(pq);
}


int priority_queue_empty(const priority_queue *pq)
{
    return heap_empty(pq);
}

int priority_queue_size(const priority_queue *pq)
{
    return heap_size(pq);
}

void priority_queue_clear(priority_queue *pq)
{
    heap_clear(pq);
}


void *priority_queue_front(priority_queue *pq)
{
    return heap_front(pq);
}

void priority_queue_push(priority_queue *pq, void *item)
{
    heap_push(pq, item);
}

void *priority_queue_pop(priority_queue *pq)
{
    return heap_pop(pq);
}
