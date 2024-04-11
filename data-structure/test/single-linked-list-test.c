#include "../include/single-linked-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void print(const single_linked_list *list)
{
    iterator begin = single_linked_list_begin(list);
    iterator end = single_linked_list_end(list);

    for (iterator itr = begin; itr != end; itr = single_linked_list_next(itr))
    {
        int *data = (int *)single_linked_list_iter_get(itr);
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
    single_linked_list *list = init_single_linked_list(free, comp);

    single_linked_list_front(list);
    single_linked_list_back(list);
    single_linked_list_delete_front(list);
    single_linked_list_delete_back(list);

    single_linked_list_insert_front(list, new_data(1));
    single_linked_list_insert_front(list, new_data(2));
    single_linked_list_insert_front(list, new_data(3));
    print(list);


    single_linked_list_delete_front(list);
    print(list);

    single_linked_list_delete_back(list);
    print(list);

    single_linked_list_clear(list);

    single_linked_list_insert_back(list, new_data(1));
    single_linked_list_insert_back(list, new_data(2));
    single_linked_list_insert_back(list, new_data(3));
    print(list);

    single_linked_list_delete_front(list);
    print(list);

    single_linked_list_delete_back(list);
    print(list);

    single_linked_list_clear(list);
    
    single_linked_list_insert_back(list, new_data(1));
    single_linked_list_insert_back(list, new_data(2));
    single_linked_list_insert_back(list, new_data(3));
    single_linked_list_insert_back(list, new_data(4));
    single_linked_list_insert_back(list, new_data(5));
    print(list);

    int *find_data = (int *)malloc(sizeof(int));
    int *result = NULL;

    *find_data = 1;
    result = (int *)single_linked_list_find_item(list, find_data);
    if (result == NULL)
        printf("%d is not found!\n", *find_data);
    else
        printf("%d is found!\n", *find_data);

    *find_data = 32767;
    result = (int *)single_linked_list_find_item(list, find_data);
    if (result == NULL)
        printf("%d is not found!\n", *find_data);
    else
        printf("%d is found!\n", *find_data);

    free(find_data);

    int idx;
    idx = 0;
    result = (int *)single_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = 2;
    result = (int *)single_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = -1;
    result = (int *)single_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    idx = 999;
    result = (int *)single_linked_list_at(list, idx);
    printf("at(%d) = %p\n", idx, result);
    
    single_linked_list_insert_at(list, 0, new_data(10));
    single_linked_list_insert_at(list, 1, new_data(10));
    single_linked_list_insert_at(list, 2, new_data(10));
    print(list);

    single_linked_list_delete_at(list, 0);
    single_linked_list_delete_at(list, 1);
    single_linked_list_delete_at(list, 2);
    print(list);

    result = single_linked_list_front(list);
    printf("front(): %d\n", *result);
    result = single_linked_list_back(list);
    printf("back(): %d\n", *result);

    single_linked_list_reverse(list);
    print(list);

    result = single_linked_list_front(list);
    printf("front(): %d\n", *result);
    result = single_linked_list_back(list);
    printf("back(): %d\n", *result);

    destroy_single_linked_list(list);
    
    return 0;
}