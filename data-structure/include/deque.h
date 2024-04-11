#ifndef _DEQUE_H_
#define _DEQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "double-linked-list.h"

typedef double_linked_list deque;

deque *init_deque(void (*free_item)(void *));
void destroy_deque(deque *dq);

int deque_empty(const deque *dq);
int deque_size(const deque *dq);

void *deque_front(const deque *dq);
void *deque_back(const deque *dq);
void deque_push_front(deque *dq, void *item);
void deque_push_back(deque *dq, void *item);
void *deque_pop_front(deque *dq);
void *deque_pop_back(deque *dq);
void deque_clear(deque *dq);

#ifdef __cplusplus
}
#endif

#endif  /* _DEQUE_H_ */