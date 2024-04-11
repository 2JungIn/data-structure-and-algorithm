#include "../include/array-deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int main(void)
{
    array_deque *dq = init_array_deque(free);

    array_deque_back(dq);
    array_deque_front(dq);
    array_deque_pop_back(dq);
    array_deque_pop_front(dq);

    array_deque_push_front(dq, new_data(1));
    array_deque_push_front(dq, new_data(2));
    array_deque_push_front(dq, new_data(3));
    array_deque_push_back(dq, new_data(4));
    array_deque_push_back(dq, new_data(5));
    array_deque_push_back(dq, new_data(6));

    int *front, *back;
    front = array_deque_front(dq);
    back = array_deque_back(dq);
    printf("%d %d\n", *front, *back);
    array_deque_pop_front(dq);
    array_deque_pop_back(dq);

    front = array_deque_front(dq);
    back = array_deque_back(dq);
    printf("%d %d\n", *front, *back);
    array_deque_pop_front(dq);
    array_deque_pop_back(dq);

    front = array_deque_front(dq);
    back = array_deque_back(dq);
    printf("%d %d\n", *front, *back);
    array_deque_pop_front(dq);
    array_deque_pop_back(dq);

    destroy_array_deque(dq);

    return 0;
}