/**
 * insertion-sort.c
 * 
 * 삽입정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void print_array(const int *arr, const int n);


int compare(const int a, const int b)
{
    // return a < b;
    return a > b;
}

void insertion_sort(int *arr, const int n, int (*comp)(const int, const int))
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        int key = arr[j];
        printf("%dth: ", i - 1);
        for ( ; j > 0 && comp(arr[j - 1], key); j--)
            arr[j] = arr[j - 1];
        arr[j] = key;
        print_array(arr, n);
    }
}


int main(void)
{
    int arr[] = { 31, 25, 12, 22, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("arr: ");
    print_array(arr, n);
    printf("\n");

    insertion_sort(arr, n, compare);

    return 0;
}


void print_array(const int *arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}
