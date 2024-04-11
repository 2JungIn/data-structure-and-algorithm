#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "heap.h"

typedef heap priority_queue;

priority_queue *init_priority_queue(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_priority_queue(priority_queue *pq);

int priority_queue_empty(const priority_queue *pq);
int priority_queue_size(const priority_queue *pq);
void priority_queue_clear(priority_queue *pq);

void *priority_queue_front(priority_queue *pq);
void priority_queue_push(priority_queue *pq, void *item);
void *priority_queue_pop(priority_queue *pq);

#ifdef __cplusplus
}
#endif

#endif  /* _PRIORITY_QUEUE_H_ */