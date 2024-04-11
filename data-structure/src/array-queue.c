#include "../include/array-queue.h"
#include <stdlib.h>


const static int default_capacity = 15;


array_queue *init_array_queue(void (*free_item)(void *))
{   
    array_queue *q = NULL;
    if ((q = (array_queue *)malloc(sizeof(array_queue))) == NULL)    /* error: malloc() */
        return NULL;
    
    if ((q->memory = (void **)malloc(sizeof(void *) * default_capacity)) == NULL)   /* error: malloc() */
    {
        free(q);
        return NULL;
    }

    q->capacity = default_capacity;
    q->front = q->rear = 0;

    q->free_item = free_item;

    return q;
}

void destroy_array_queue(array_queue *q)
{
    if (q == NULL)    /* error: invalid arg */
        return ;
    
    array_queue_clear(q);
    free(q->memory);
    free(q);
}

void array_queue_print(const array_queue *q, void (*print_func)(const void *))
{
    if (q == NULL)  /* error: invalid arg */
        return ;

    if (print_func == NULL)
        return ;

    for (int i = 0; i < array_queue_size(q); i++)
        print_func(q->memory[i]);
}


int array_queue_full(const array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return -1;

    return (q->rear + 1) % q->capacity == q->front;
}

int array_queue_empty(const array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return -1;

    return q->front == q->rear;
}

int array_queue_size(const array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return -1;

    if (array_queue_empty(q))
        return 0;

    int size = q->rear - q->front;
    
    if (q->front < q->rear)
        return size;
    
    return size + q->capacity;
}

int array_queue_resize(array_queue *q, const int size)
{
    if (q == NULL)   /* error: invalid arg */
        return -1;

    if (size <= 1)   /* error: size는 1보다 커야 한다. */
        return -1;

    int new_capacity = size;
    void **new_memory = NULL;
    if ((new_memory = (void **)malloc(sizeof(void *) * new_capacity)) == NULL)  /* error: malloc() */
        return -1;

    int count = 0;
    if (new_capacity < q->capacity)
    {
        int i = q->front;
        for ( ; count < size; count++)
            new_memory[count] = q->memory[i++];

        void (*free_item)(void *) = q->free_item;
        if (free_item)
        {
            for ( ; i != q->rear; i = (i + 1) % q->capacity)
                free_item(q->memory[i]);
        }

        q->front = 0;
        q->rear = size - 1;
    }
    else
    {
        for (int i = q->front; i != q->rear; i = (i + 1) % q->capacity)
            new_memory[count++] = q->memory[i];
    }

    free(q->memory);
    q->capacity = new_capacity;
    q->memory = new_memory;

    return 0;
}


void *array_queue_front(const array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return NULL;

    if (array_queue_empty(q))
        return NULL;
    
    return q->memory[q->front];
}

void array_queue_enqueue(array_queue *q, void *item)
{
    if (q == NULL)  /* error: invalid arg */
        return ;

    if (item == NULL)   /* error: invalid arg */
        return ;

    if (array_queue_full(q))
        array_queue_resize(q, q->capacity * 2);
    
    q->memory[q->rear] = item;
    q->rear = (q->rear + 1) % q->capacity;
}

void *array_queue_dequeue(array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return NULL;
    
    if (array_queue_empty(q))
        return NULL;
    
    void *ret_item = NULL;
    
    void (*free_item)(void *) = q->free_item;
    if (free_item)
        free_item(q->memory[q->front]);
    else
        ret_item = q->memory[q->front];

    q->front = (q->front + 1) % q->capacity;

    return ret_item;
}


void array_queue_clear(array_queue *q)
{
    if (q == NULL)  /* error: invalid arg */
        return ;

    while (!array_queue_empty(q))
        array_queue_dequeue(q);

    q->front = q->rear = 0;
}
