#include "../include/double-linked-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void print(const double_linked_list *list)
{
    iterator begin = double_linked_list_begin(list);
    iterator end = double_linked_list_end(list);

    for (iterator itr = begin; itr != end; itr = double_linked_list_next(itr))
    {
        int *data = (int *)double_linked_list_iter_get(itr);
        printf("[%d] ", *data);
    }

    printf("\n");
}

int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int main(void)
{
    double_linked_list *list = init_double_linked_list(free, comp);

    double_linked_list_front(list);
    double_linked_list_back(list);
    double_linked_list_delete_front(list);
    double_linked_list_delete_back(list);

    double_linked_list_insert_front(list, new_data(1));
    double_linked_list_insert_front(list, new_data(2));
    double_linked_list_insert_front(list, new_data(3));
    print(list);


    double_linked_list_delete_front(list);
    print(list);

    double_linked_list_delete_back(list);
    print(list);

    double_linked_list_clear(list);

    double_linked_list_insert_back(list, new_data(1));
    double_linked_list_insert_back(list, new_data(2));
    double_linked_list_insert_back(list, new_data(3));
    print(list);


    double_linked_list_delete_front(list);
    print(list);

    double_linked_list_delete_back(list);
    print(list);

    double_linked_list_clear(list);
    
    double_linked_list_insert_back(list, new_data(1));
    double_linked_list_insert_back(list, new_data(2));
    double_linked_list_insert_back(list, new_data(3));
    double_linked_list_insert_back(list, new_data(4));
    double_linked_list_insert_back(list, new_data(5));
    print(list);

    int *find_data = (int *)malloc(sizeof(int));
    int *result = NULL;

    *find_data = 1;
    result = (int *)double_linked_list_find_item(list, find_data);
    if (result == NULL)
        printf("%d is not found!\n", *find_data);
    else
        printf("%d is found!\n", *find_data);

    *find_data = 32767;
    result = (int *)double_linked_list_find_item(list, find_data);
    if (result == NULL)
        printf("%d is not found!\n", *find_data);
    else
        printf("%d is found!\n", *find_data);

    free(find_data);

    int idx;
    idx = 0;
    result = (int *)double_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = 2;
    result = (int *)double_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = -1;
    result = (int *)double_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = 999;
    result = (int *)double_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    

    double_linked_list_insert_at(list, 0, new_data(10));
    double_linked_list_insert_at(list, 1, new_data(20));
    double_linked_list_insert_at(list, 2, new_data(30));
    print(list);

    double_linked_list_delete_at(list, 0);
    double_linked_list_delete_at(list, 1);
    double_linked_list_delete_at(list, 2);
    print(list);

    result = double_linked_list_front(list);
    printf("front(): %d\n", *result);
    result = double_linked_list_back(list);
    printf("back(): %d\n", *result);

    double_linked_list_reverse(list);
    print(list);

    result = double_linked_list_front(list);
    printf("front(): %d\n", *result);
    result = double_linked_list_back(list);
    printf("back(): %d\n", *result);

    destroy_double_linked_list(list);
    
    return 0;
}