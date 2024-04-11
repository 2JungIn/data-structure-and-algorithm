#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/array-queue.h"

int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int main(void)
{
    int n, k;
    if (scanf("%d %d", &n, &k) < 2)
    {
        fprintf(stderr, "input error!\n");
        return -1;
    }

    array_queue *q = init_array_queue(NULL);

    array_queue_dequeue(q);
    array_queue_front(q);

    for (int i = 1; i <= n; i++)
        array_queue_enqueue(q, new_data(i));

    printf("<");
    int idx = 0;
    while (array_queue_size(q) > 1)
    {
        idx = (idx + 1) % k;
        if (idx == 0)
        {
            int *front = array_queue_dequeue(q);
            printf("%d, ", *front);
            free(front);
        }
        else
        {
            array_queue_enqueue(q, array_queue_dequeue(q));
        }
    }

    int *front = array_queue_front(q);
    printf("%d>\n", *front);
    free(front);

    destroy_array_queue(q);

    return 0;
}