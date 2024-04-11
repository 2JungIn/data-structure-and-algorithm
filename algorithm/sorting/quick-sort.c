/**
 * quick-sort.c
 * 
 * 퀵정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void swap(int* a, int* b);
void print_array(const int *arr, const int n, const int start, const int end);


int compare(const int a, const int b)
{
    // return a < b;
    return a > b;
}

int partition(int *arr, const int low, const int high, int (*comp)(const int, const int), const int n) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;

    while (1)
    {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);

        printf("pivot(%2d), i(%2d), j(%2d)\t", pivot, i, j);
        print_array(arr, n, low, high);

        if (i >= j)
            break;

        swap(&arr[i], &arr[j]);
    }

    return j;
}

void quick_sort(int *arr, const int low, const int high, int (*comp)(const int, const int), const int n)
{
    if (low < high)
    {
        int p = partition(arr, low, high, comp, n);

        quick_sort(arr, low, p, comp, n);
        quick_sort(arr, p + 1, high, comp, n);
    }
}


int main(void)
{
    int arr[] = { 5, 3, 7, 6, 2, 1, 4  };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("                before: ");
    print_array(arr, n, 0, n - 1);
    printf("\n");

    quick_sort(arr, 0, n - 1, compare, n);
    printf("\n");
    
    printf("                 after: ");
    print_array(arr, n, 0, n - 1);
    printf("\n");

    return 0;
}


void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(const int *arr, const int n, const int start, const int end)
{
    for (int i = 0; i < n; i++)
    {
        if (i >= start && i <= end)
            printf("%2d ", arr[i]);
        else
            printf("   ");
    }

    printf("\n");
}
