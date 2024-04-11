/**
 * randomized-quick-sort.c
 * 
 * 랜덤 피벗을 사용한 퀵정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n, const int lo, const int hi);


int partition(int *arr, const int lo, const int hi)
{
    int pivot = arr[hi];
    printf("pivot:    %d\n", pivot);
    int i = lo - 1;
    for (int j = lo; j < hi; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[hi]);

    return i + 1;
}

int randomized_partition(int *arr, const int lo, const int hi)
{
    int random = lo + (rand() % (hi - lo + 1));
    
    swap(&arr[random], &arr[hi]);

    return partition(arr, lo, hi);
}

void randomized_quick_sort(int *arr, const int n, const int lo, const int hi)
{
    if (lo < hi)
    {
        print_array(arr, n, lo, hi);
        printf("\n");

        int p = randomized_partition(arr, lo, hi);
        randomized_quick_sort(arr, n, lo, p - 1);
        randomized_quick_sort(arr, n, p + 1, hi);
    }
}


int main(void)
{
    srand(time(NULL));

    int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, };
    int n = sizeof(arr) / sizeof(arr[0]);

    randomized_quick_sort(arr, n, 0, n - 1);

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
        printf("%d ", i);
    printf("\n");

    printf("array:    ");
    for (int i = 0; i < n; i++)
    {
        if (i >= lo && i <= hi)
            printf("%d ", arr[i]);
        else
            printf("  ");
    }
    printf("\n");
}
