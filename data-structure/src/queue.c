#include "../include/queue.h"
#include <stddef.h>

queue *init_queue(void (*free_item)(void *))
{
    return init_single_linked_list(free_item, NULL);
}

void destroy_queue(queue *q)
{
    destroy_single_linked_list(q);
}


int queue_empty(const queue *q)
{
    return single_linked_list_empty(q);
}

int queue_size(const queue *q)
{
    return single_linked_list_size(q);
}


void *queue_front(const queue *q)
{
    return single_linked_list_front(q);
}

void queue_enqueue(queue *q, void *item)
{
    single_linked_list_insert_back(q, item);
}

void *queue_dequeue(queue *q)
{
    return single_linked_list_delete_front(q);
}

void queue_clear(queue *q)
{
    single_linked_list_clear(q);
}
