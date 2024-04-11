/**
 * interpolation-search.c
 * 
 * 보간탐색 알고리즘을 사용해서 값을 찾는 프로그램입니다.
**/

#include <stdio.h>

void swap(int *a, int *b);
int compare(const int a, const int b);
void print_array(const int *arr, const int n);
void selection_sort(int *arr, const int n, int (*comp)(const int, const int));


int interpolation_search(const int *arr, const int low, const int high, const int find_value)
{
    if (low <= high && find_value >= arr[low] && find_value <= arr[high])
    {
        int pos = low + (int)((double)(high - low) / (arr[high] - arr[low]) * (find_value - arr[low]));

        if (find_value == arr[pos])
            return pos;
        
        if (find_value < arr[pos])
            return interpolation_search(arr, low, pos - 1, find_value);
        
        if (find_value > arr[pos])
            return interpolation_search(arr, pos + 1, high, find_value);
    }

    return -1;  /* not found */
}


int main(void)
{
    int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 }; /* 위키피디아 예시 */
    int n = sizeof(arr) / sizeof(arr[0]);

    selection_sort(arr, n, compare);
    
    int find_values[] = { 0, 10, 50, 20, 47, 32, 13 };
    int m = sizeof(find_values) / sizeof(find_values[0]);

    print_array(arr, n);

    for (int i = 0; i < m; i++)
    {
        int find_value = find_values[i];
        int result = interpolation_search(arr, 0, n - 1, find_value);

        if (result == -1)
            printf("%d is not found!\n", find_value);
        else
            printf("%d is found index: %d\n", find_value, result);
    }

    return 0;
}


void print_array(const int *arr, const int n)
{
    printf("          index:  ");
    for (int i = 0; i < n; i++)
        printf("%2d ", i);
    printf("\n");

    printf("          array:  ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
