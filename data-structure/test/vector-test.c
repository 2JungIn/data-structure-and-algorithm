#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/vector.h"

int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

void print(const void *data)
{
    printf("[%d] ", *(int *)data);
}

int main(void)
{
    vector *v = init_vector(1, free);

    vector_pop_back(v);

    for (int i = 0; i < 5; i++)
        vector_push_back(v, new_data(i));
    print_vector(v, print);
    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        vector_left_shift(v);
        print_vector(v, print);
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        vector_right_shift(v);
        print_vector(v, print);
        printf("\n");
    }
    printf("\n");


    vector_insert_at(v, 3, new_data(10));
    print_vector(v, print);
    printf("\n");

    
    vector_pop_back(v);
    print_vector(v, print);
    printf("\n");


    vector_delete_at(v, 4);
    print_vector(v, print);
    printf("\n");


    vector_reverse(v);
    print_vector(v, print);
    printf("\n");


    vector_resize(v, 1);
    print_vector(v, print);
    printf("\n");
    

    vector_clear(v);

    destroy_vector(v);

    return 0;
}