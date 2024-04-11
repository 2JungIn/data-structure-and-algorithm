#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct array_queue 
{
    int capacity;

    void **memory;
    int front;
    int rear;

    void (*free_item)(void *);
} array_queue;


array_queue *init_array_queue(void (*free_item)(void *));
void destroy_array_queue(array_queue *q);
void array_queue_print(const array_queue *q, void (*print_func)(const void *));

int array_queue_full(const array_queue *q);
int array_queue_empty(const array_queue *q);
int array_queue_size(const array_queue *q);
int array_queue_resize(array_queue *q, const int size);

void *array_queue_front(const array_queue *q);
void array_queue_enqueue(array_queue *q, void *item);
void *array_queue_dequeue(array_queue *q);
void array_queue_clear(array_queue *q);

#ifdef __cplusplus
}
#endif

#endif  /* _ARRAY_QUEUE_H_ */