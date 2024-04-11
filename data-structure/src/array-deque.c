#include "../include/array-deque.h"
#include <stdlib.h>


const static int default_capacity = 15;


array_deque *init_array_deque(void (*free_item)(void *))
{
    array_deque *dq = NULL;
    if ((dq = (array_deque *)malloc(sizeof(array_deque))) == NULL)    /* error: malloc() */
        return NULL;
    
    if ((dq->memory = (void **)malloc(sizeof(void *) * default_capacity)) == NULL)   /* error: malloc() */
    {
        free(dq);
        return NULL;
    }

    dq->capacity = default_capacity;
    dq->front = dq->rear = 0;

    dq->free_item = free_item;

    return dq;
}

void destroy_array_deque(array_deque *dq)
{
    if (dq == NULL)    /* error: invalid arg */
        return ;
    
    array_deque_clear(dq);
    free(dq->memory);
    free(dq);
}

void array_deque_print(const array_deque *dq, void (*print_func)(const void *))
{
    if (dq == NULL)  /* error: invalid arg */
        return ;

    if (print_func == NULL)
        return ;

    for (int i = 0; i < array_deque_size(dq); i++)
        print_func(dq->memory[i]);
}


int array_deque_full(const array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return -1;

    return (dq->rear + 1) % dq->capacity == dq->front;
}

int array_deque_empty(const array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return -1;

    return dq->front == dq->rear;
}

int array_deque_size(const array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return -1;

    if (array_deque_empty(dq))
        return 0;

    int size = dq->rear - dq->front;
    
    if (dq->front < dq->rear)
        return size;
    
    return size + dq->capacity;
}

int array_deque_resize(array_deque *dq, const int size)
{
    if (dq == NULL)   /* error: invalid arg */
        return -1;

    if (size <= 1)   /* error: size는 1보다 커야 한다. */
        return -1;

    int new_capacity = size;
    void **new_memory = NULL;
    if ((new_memory = (void **)malloc(sizeof(void *) * new_capacity)) == NULL)  /* error: malloc() */
        return -1;

    int count = 0;
    if (new_capacity < dq->capacity)
    {   
        int i = dq->front;
        for ( ; count < size; count++)
            new_memory[count] = dq->memory[i++];

        void (*free_item)(void *) = dq->free_item;
        if (free_item)
        {
            for ( ; i != dq->rear; i = (i + 1) % dq->capacity)
                free_item(dq->memory[i]);
        }

        dq->front = 0;
        dq->rear = size - 1;
    }
    else
    {
        for (int i = dq->front; i != dq->rear; i = (i + 1) % dq->capacity)
            new_memory[count++] = dq->memory[i];
    }

    free(dq->memory);
    dq->capacity = new_capacity;
    dq->memory = new_memory;

    return 0;
}


void *array_deque_front(const array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return NULL;

    if (array_deque_empty(dq))
        return NULL;
    
    int front_index = dq->front;;
    return dq->memory[front_index];
}

void *array_deque_back(const array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return NULL;

    if (array_deque_empty(dq))
        return NULL;
    
    int back_index = (dq->rear - 1 + dq->capacity) % dq->capacity;
    return dq->memory[back_index];
}

void array_deque_push_back(array_deque *dq, void *item)
{
    if (dq == NULL)  /* error: invalid arg */
        return ;

    if (item == NULL)   /* error: invalid arg */
        return ;

    if (array_deque_full(dq))
        array_deque_resize(dq, dq->capacity * 2);
    
    dq->memory[dq->rear] = item;
    dq->rear = (dq->rear + 1) % dq->capacity;
}

void array_deque_push_front(array_deque *dq, void *item)
{
    if (dq == NULL)  /* error: invalid arg */
        return ;

    if (item == NULL)   /* error: invalid arg */
        return ;

    if (array_deque_full(dq))
        array_deque_resize(dq, dq->capacity * 2);
    
    dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    dq->memory[dq->front] = item;
}

void *array_deque_pop_front(array_deque *dq)
{
    if (dq == NULL) /* error: invalid arg */
        return NULL;
    
    if (array_deque_empty(dq))
        return NULL;

    void *ret_item = NULL;
    
    void (*free_item)(void *) = dq->free_item;
    if (free_item)
        free_item(dq->memory[dq->front]);
    else
        ret_item = dq->memory[dq->front];
    
    dq->front = (dq->front + 1) % dq->capacity;

    return ret_item;
}

void *array_deque_pop_back(array_deque *dq)
{
    if (dq == NULL) /* error: invalid arg */
        return NULL;
    
    if (array_deque_empty(dq))
        return NULL;
    
    dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;

    void *ret_item = NULL;
    
    void (*free_item)(void *) = dq->free_item;
    if (free_item)
        free_item(dq->memory[dq->rear]);
    else
        ret_item = dq->memory[dq->rear];

    return ret_item;
}


void array_deque_clear(array_deque *dq)
{
    if (dq == NULL)  /* error: invalid arg */
        return ;

    while (!array_deque_empty(dq))
        array_deque_pop_front(dq);

    dq->front = dq->rear = 0;
}
