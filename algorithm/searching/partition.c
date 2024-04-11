/**
 * partition.c
 *  
 * pivot보다 작은 값들은 pivot 왼쪽으로, 큰 값들은 오른쪽으로 이동하는 프로그램입니다.
**/

#include <stdio.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n);


int partition(int *arr, const int lo, const int hi)
{
    int pivot = arr[hi];

    printf("pivot: %d\n", pivot);
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

int main(void)
{
    int arr[] = { 9, 8, 7, 6, 4, 3, 2, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("befor:  ");
    print_array(arr, n);
    printf("\n");

    printf("parition -> ");
    partition(arr, 0, n - 1);
    printf("\n");

    printf("after:  ");
    print_array(arr, n);
    printf("\n");

    return 0;
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(const int *arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}
