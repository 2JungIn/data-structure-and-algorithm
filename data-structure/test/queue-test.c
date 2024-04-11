#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/queue.h"

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

    queue *q = init_queue(NULL);

    queue_dequeue(q);
    queue_front(q);

    for (int i = 1; i <= n; i++)
        queue_enqueue(q, new_data(i));

    printf("<");
    int idx = 0;
    while (queue_size(q) > 1)
    {
        idx = (idx + 1) % k;
        if (idx == 0)
        {
            int *front = queue_dequeue(q);
            printf("%d, ", *front);
            free(front);
        }
        else
        {
            queue_enqueue(q, queue_dequeue(q));
        }
    }

    int *front = queue_dequeue(q);
    printf("%d>\n", *front);
    free(front);

    destroy_queue(q);

    return 0;
}