/**
 * shell-sort.c
 * 
 * 셸정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void print_array(const int *arr, const int n, const int start, const int gap);


int compare(const int a, const int b)
{
    // return a < b;
    return a > b;
}

void insertion_sort(int *arr, const int n, const int gap, int (*comp)(const int, const int))
{
    printf("gap: %d\n", gap);
    for (int i = gap; i < n; i++)
    {
        printf("before: ");
        print_array(arr, n, i, gap);

        int j = i;
        int key = arr[j];
        for ( ; j >= gap && comp(arr[j - gap], key); j -= gap)
            arr[j] = arr[j - gap];
        arr[j] = key;

        printf("after:  ");
        print_array(arr, n, i, gap);
    }
}

void shell_sort(int *arr, const int n, int (*comp)(const int, const int))
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        printf("        ");
        print_array(arr, n, 0, 1);

        insertion_sort(arr, n, gap, comp);
    }
}


int main(void)
{
    int arr[] = { 62, 83, 18, 53, 7, 17, 95, 86, 47, 69, 25, 28 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("arr: ");
    print_array(arr, n, 0, 1);
    printf("\n");

    shell_sort(arr, n, compare);
    printf("\n");

    printf("arr: ");
    print_array(arr, n, 0, 1);
    printf("\n");

    return 0;
}


void print_array(const int *arr, const int n, const int start, const int gap)
{
    for (int i = 0; i < n; i++)
    {
        if ((i - start) % gap == 0)
            printf("%2d ", arr[i]);
        else
            printf("   ");
    }
    
    printf("\n");
}
