#include "../include/stack.h"
#include <stddef.h>

stack *init_stack(void (*free_item)(void *))
{
    return init_single_linked_list(free_item, NULL);
}

void destroy_stack(stack *s)
{
    destroy_single_linked_list(s);
}


int stack_empty(const stack *s)
{
    return single_linked_list_empty(s);
}

int stack_size(const stack *s)
{
    return single_linked_list_size(s);
}


void *stack_top(const stack *s)
{
    return single_linked_list_front(s);
}

void stack_push(stack *s, void *item)
{
    single_linked_list_insert_front(s, item);
}

void *stack_pop(stack *s)
{
    return single_linked_list_delete_front(s);
}

void stack_clear(stack *s)
{
    single_linked_list_clear(s);
}
