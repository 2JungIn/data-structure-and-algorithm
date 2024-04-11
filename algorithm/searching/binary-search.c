/**
 * binary-search.c
 * 
 * 이진탐색 알고리즘을 사용해서 값을 찾는 프로그램입니다.
**/

#include <stdio.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n, const int start, const int end);
int compare(const int a, const int b);
void selection_sort(int *arr, const int n, int (*comp)(const int, const int));


int binary_search(const int *arr, const int n, const int find_value)
{
    int left = 0;
    int right = n - 1;
    int middle = -1;

    while (left <= right)
    {
        middle = (left + right) / 2;

        printf("middle(%d), range(%d:%d):\t", middle, left, right);
        print_array(arr, n, left, right);

        if (arr[middle] < find_value)
            left = middle + 1;
        else if (arr[middle] > find_value)
            right = middle - 1;
        else 
            return middle;
    }

    return -1;  /* not found */
}


int main(void)
{
    int arr[] = { 2, 4, 1, 5, 3, 7, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    selection_sort(arr, n, compare);
    
    int find_values[] = { 0, 2, 3, 5, 7, 9, 10};
    int m = sizeof(find_values) / sizeof(find_values[0]);
    for (int i = 0; i < m; i++)
    {
        int find_value = find_values[i];

        printf("\nfind value: %2d  index:\t", find_value);
        for (int i = 0; i < n; i++)
            printf("%d ", i);
        printf("\n\n");

        int result = binary_search(arr, n, find_value);

        if (result == -1)
            printf("\n%d is not found!\n", find_value);
        else
            printf("\n%d is found index: %d\n", find_value, result);
        
        printf("\n");
    }

    return 0;
}


void swap(int *a, int *b)
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
            printf("%d ", arr[i]);
        else
            printf("  ");
    }

    printf("\n");
}

int compare(const int a, const int b)
{
    return a < b;
    // return a > b;
}

void selection_sort(int *arr, const int n, int (*comp)(const int, const int))
{
    for (int i = 0; i < n - 1; i++)
    {
        int selected_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (comp(arr[j], arr[selected_index]))
            {
                selected_index = j;
            }
        }
        swap(&arr[i], &arr[selected_index]);
    }
}
