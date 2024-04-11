/**
 * partial-selection-sort.c
 * 
 * 부분 선택정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n);


int compare(const int a, const int b)
{
    return a < b;
    // return a > b;
}

void selection_sort(int *arr, const int n, const int start, int (*comp)(const int, const int))
{
    int select_index = start;
    for (int i = start + 1; i < n; i++)
    {
        if (comp(arr[i], arr[select_index]))
        {
            select_index = i;
        }
    }
    swap(&arr[start], &arr[select_index]);
}

void partial_selection_sort(int *arr, const int n, int k, int (*comp)(const int, const int))
{
    printf("arr: ");
    print_array(arr, n);
    printf("\n");

    for (int i = 0; i < k; i++)
    {
        selection_sort(arr, n, i, comp);
        printf("%dth: ", i);
        print_array(arr, n);
    }
}


int main(void)
{
    int arr[] = { 7, 10, 4, 3, 20, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int k = 3;
    partial_selection_sort(arr, n, k, compare);

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
        printf("%2d ", arr[i]);
    printf("\n");
}
