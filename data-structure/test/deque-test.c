#include "../include/deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int main(void)
{
    deque *dq = init_deque(free);

    deque_back(dq);
    deque_front(dq);
    deque_pop_back(dq);
    deque_pop_front(dq);

    deque_push_front(dq, new_data(1));
    deque_push_front(dq, new_data(2));
    deque_push_front(dq, new_data(3));
    deque_push_back(dq, new_data(4));
    deque_push_back(dq, new_data(5));
    deque_push_back(dq, new_data(6));

    int *front, *back;
    front = deque_front(dq);
    back = deque_back(dq);
    printf("%d %d\n", *front, *back);
    deque_pop_front(dq);
    deque_pop_back(dq);

    front = deque_front(dq);
    back = deque_back(dq);
    printf("%d %d\n", *front, *back);
    deque_pop_front(dq);
    deque_pop_back(dq);

    front = deque_front(dq);
    back = deque_back(dq);
    printf("%d %d\n", *front, *back);
    deque_pop_front(dq);
    deque_pop_back(dq);

    destroy_deque(dq);

    return 0;
}