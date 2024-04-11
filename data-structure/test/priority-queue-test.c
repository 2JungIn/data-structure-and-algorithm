#include "../include/priority-queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int comp(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

void print(void *data)
{
    printf("%d ", *(int *)data);
}

int main(void)
{
    priority_queue *pq = init_priority_queue(free, comp);

    for (int i = 0; i < 19; i++)
        priority_queue_push(pq, new_data(i));

    while (!priority_queue_empty(pq))
    {
        void *front = priority_queue_front(pq);
        print(front);
        priority_queue_pop(pq);
    }
    printf("\n");

    destroy_priority_queue(pq);

    return 0;
}