/**
 * radix-sort.c
 * 
 * 기수정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../data-structure/include/queue.h"

void print_array(const int *arr, const int n);
void init(queue **q, const int n);
void release(queue **q, const int n);


void radix_sort(int *arr, const int n)
{
    queue *queues[10];
    init(queues, 10);

    // 배열의 최댓값을 찾는다.
    int max_value = arr[0];
    for (int i = 1; i < n; i++)
        if (max_value < arr[i])
            max_value = arr[i];

    for (int exp = 1; max_value / exp > 0; exp *= 10)
    {
        printf("%d의 자리를 기준으로 정렬:\t", exp);
        for (int i = 0; i < n; i++)
            queue_enqueue(queues[(arr[i] / exp) % 10], &arr[i]);
        
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            while (!queue_empty(queues[i]))
            {
                int *item = (int *)queue_dequeue(queues[i]);
                
                arr[count] = *item;

                count++;
            }
        }

        print_array(arr, n);
    }
    printf("\n");

    release(queues, 10);
}


int main(void)
{
    int arr[] = { 170, 45, 75, 90, 2, 24, 802, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("정렬하기 전의 배열:             ");
    print_array(arr, n);
    printf("\n");
    
    radix_sort(arr, n);

    printf("정렬한 후의 배열:               ");
    print_array(arr, n);
    printf("\n");

    return 0;
}


void print_array(const int *arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%03d ", arr[i]);
    
    printf("\n");
}

void init(queue **q, const int n)
{
    for (int i = 0; i < n; i++)
        q[i] = init_queue(NULL);
}

void release(queue **q, const int n)
{
    for (int i = 0; i < n; i++)
        destroy_queue(q[i]);
}
