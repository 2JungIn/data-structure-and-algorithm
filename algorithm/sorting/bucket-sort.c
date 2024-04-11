/**
 * bucket-sort.c
 * 
 * 버킷 정렬을 사용해서 배열을 정렬하는 프로그램입니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../data-structure/include/vector.h"


int *new_int(int i);
void print_int(const void *item);
int compare(const int a, const int b);
void print_array(const int *arr, const int n);
void selection_sort(vector *v, int (*comp)(const int, const int));
void print_buckets(vector **buckets, const int n);


void bucket_sort(int *arr, const int n, const int num_buckets, int (*comp)(const int, const int))
{
    /* buckets init */
    vector *buckets[num_buckets];
    for (int i = 0; i < num_buckets; i++)
        buckets[i] = init_vector(0, free);

    for (int i = 0; i < n; i++)
    {        
        int bucket_index = arr[i] / num_buckets;
        vector_push_back(buckets[bucket_index], new_int(arr[i]));
    }

    printf("before:\n");
    print_buckets(buckets, num_buckets);
    printf("\n");

    // TODO:
    for (int i = 0; i < num_buckets; i++)
        selection_sort(buckets[i], compare);

    printf("after:\n");
    print_buckets(buckets, num_buckets);
    printf("\n");

    int cnt = 0;
    for (int i = 0; i < num_buckets; i++)
        for (int j = 0; j < vector_size(buckets[i]); j++)
            arr[cnt++] = *(int *)vector_get_at(buckets[i], j);

    /* buckets release */
    for (int i = 0; i < num_buckets; i++)
        destroy_vector(buckets[i]);
}


int main(void)
{
    int arr[] = { 62, 72, 96, 15, 64, 18, 60, 40, 67, 49, 2, 20, 1, 61, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, n);

    bucket_sort(arr, n, 10, compare);

    print_array(arr, n);

    return 0;
}


int *new_int(int item)
{
    return (int *)memcpy(malloc(sizeof(int)), &item, sizeof(int));
}

void print_int(const void *item)
{
    printf("%2d ", *(int *)item);
}

int compare(const int a, const int b)
{
    return a < b;
    // return a > b;
}

void print_array(const int *arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n\n");
}

void selection_sort(vector *v, int (*comp)(const int, const int))
{
    for (int i = 0; i < vector_size(v) - 1; i++)
    {
        int selected_index = i;
        for (int j = i + 1; j < vector_size(v); j++)
        {
            if (comp(*(int *)vector_get_at(v, j), *(int *)vector_get_at(v, selected_index)))
            {
                selected_index = j;
            }
        }
        vector_swap(v, i, selected_index);
    }
}

void print_buckets(vector **buckets, const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%2d:  ", i);
        print_vector(buckets[i], print_int);
        printf("\n");
    }
}