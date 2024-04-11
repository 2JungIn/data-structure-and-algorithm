/**
 * selection-sort.c
 * 
 * 선택정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n);


int compare(const int a, const int b)
{
    return a < b;
    // return a > b;
}

void selection_sort(int *arr, const int n, int (*comp)(const int, const int))
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("%dth: ", i);
        int selected_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (comp(arr[j], arr[selected_index]))
            {
                selected_index = j;
            }
        }
        swap(&arr[i], &arr[selected_index]);
        print_array(arr, n);
    }
}


int main(void)
{
    int arr[] = { 64, 25, 12, 22, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("arr: ");
    print_array(arr, n);
    printf("\n");

    selection_sort(arr, n, compare);

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
