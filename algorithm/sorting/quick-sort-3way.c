/**
 * quick-sort-3way.c
 * 
 * 분할 횟수를 최소화 하는 퀵정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n, const int lo, const int hi);


void quick_sort_3way(int *arr, const int n, const int lo, const int hi)
{
    if (hi <= lo) 
        return ;

    int lt = lo, i = lo + 1, gt = hi;
    int v = arr[lo];

    printf("key = %d\n", v);

    while (i <= gt)
    {
        if (arr[i] < v)
        {
            swap(&arr[i], &arr[lt]);
            lt++;
        }
        else if (arr[i] > v)
        {
            swap(&arr[i], &arr[gt]);
            gt--;
            continue;
        }
        
        i++;
    }

    print_array(arr, n, lo, hi);
    printf("\n");

    quick_sort_3way(arr, n, lo, lt - 1);
    quick_sort_3way(arr, n, gt + 1, hi);
}

int main(void)
{
    srand(time(NULL));

    int arr[] = { 7, 7, 7, 6, 3, 3, 8, 8, 2, 6, 8, 5, 4, 2, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, n, 0, n - 1);

    quick_sort_3way(arr, n, 0, n - 1);

    print_array(arr, n, 0, n - 1);

    return 0;
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(const int *arr, const int n, const int lo, const int hi)
{
    printf("index:    ");
    for (int i = 0; i < n; i++)
        printf("%2d ", i);
    printf("\n");

    printf("array:    ");
    for (int i = 0; i < n; i++)
    {
        if (i >= lo && i <= hi)
            printf("%2d ", arr[i]);
        else
            printf("  ");
    }
    printf("\n");
}
