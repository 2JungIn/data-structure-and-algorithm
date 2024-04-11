#ifndef _ARRAY_DEQUE_H_
#define _ARRAY_DEQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct array_deque 
{
    int capacity;

    void **memory;
    int front;
    int rear;

    void (*free_item)(void *);
} array_deque;


array_deque *init_array_deque(void (*free_item)(void *));
void destroy_array_deque(array_deque *q);
void array_deque_print(const array_deque *q, void (*print_func)(const void *));

int array_deque_full(const array_deque *q);
int array_deque_empty(const array_deque *q);
int array_deque_size(const array_deque *q);
int array_deque_resize(array_deque *q, const int size);

void *array_deque_front(const array_deque *q);
void *array_deque_back(const array_deque *q);
void array_deque_push_front(array_deque *q, void *item);
void array_deque_push_back(array_deque *q, void *item);
void *array_deque_pop_front(array_deque *q);
void *array_deque_pop_back(array_deque *q);
void array_deque_clear(array_deque *q);

#ifdef __cplusplus
}
#endif

#endif  /* _ARRAY_DEQUE_H_ */