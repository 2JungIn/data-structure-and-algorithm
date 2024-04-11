#include "../include/deque.h"
#include <stddef.h>

deque *init_deque(void (*free_item)(void *))
{
    return init_double_linked_list(free_item, NULL);
}

void destroy_deque(deque *dq)
{
    destroy_double_linked_list(dq);
}


int deque_empty(const deque *dq)
{
    return double_linked_list_empty(dq);
}

int deque_size(const deque *dq)
{
    return double_linked_list_size(dq);
}


void *deque_front(const deque *dq)
{
    return double_linked_list_front(dq);
}

void *deque_back(const deque *dq)
{
    return double_linked_list_back(dq);
}

void deque_push_front(deque *dq, void *item)
{
    double_linked_list_insert_front(dq, item);
}

void deque_push_back(deque *dq, void *item)
{
    double_linked_list_insert_back(dq, item);
}

void *deque_pop_front(deque *dq)
{
    return double_linked_list_delete_front(dq);
}

void *deque_pop_back(deque *dq)
{
    return double_linked_list_delete_back(dq);
}

void deque_clear(deque *dq)
{
    double_linked_list_clear(dq);
}
