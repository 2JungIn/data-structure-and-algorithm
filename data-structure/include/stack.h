#ifndef _STACK_H_
#define _STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "single-linked-list.h"

typedef single_linked_list stack;

stack *init_stack(void (*free_item)(void *));
void destroy_stack(stack *s);

int stack_empty(const stack *s);
int stack_size(const stack *s);

void *stack_top(const stack *s);
void stack_push(stack *s, void *item);
void *stack_pop(stack *s);
void stack_clear(stack *s);

#ifdef __cplusplus
}
#endif

#endif  /* _STACK_H_ */