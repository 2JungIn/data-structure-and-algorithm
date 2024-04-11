#include "../include/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void print(const void *data)
{
    printf("%d ", *(int *)data);
}


int main(void)
{
    heap *h = init_heap(free, comp);

    heap_pop(h);

    for (int i = 0; i < 19; i++)
        heap_push(h, new_data(i));

    print_heap(h, print);
    printf("\n");
    
    heap_sort(h);

    print_heap(h, print);
    printf("\n");

    heap_clear(h);

    for (int i = 0; i < 19; i++)
        heap_push(h, new_data(i));
        
    while (!heap_empty(h))
    {
        void *front = heap_front(h);
        print(front);
        heap_pop(h);
    }
    printf("\n");

    destroy_heap(h);

    return 0;
}