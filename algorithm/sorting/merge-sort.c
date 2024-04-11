/**
 * merge-sort.c
 * 
 * 병합정렬을 사용해서 배열을 정렬하는 프로그램입니다.
**/

#include <stdio.h>

void print_array(const int *arr, const int start, const int end);


int compare(const int a, const int b)
{
    return a < b;
    // return a > b;
}

void merge(int *arr, const int left, const int mid, const int right, int (*comp)(const int, const int))
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int left_arr[n1];
    int right_arr[n2];

    // left, right 배열 초기화
    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[mid + j + 1];

    printf("left arr: ");
    print_array(left_arr, 0, n1);
    printf("right arr: ");
    print_array(right_arr, 0, n2);

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (comp(left_arr[i], right_arr[j]))
        {
            arr[k] = left_arr[i];
            i++;
        }
        else 
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    for ( ; i < n1; i++)
        arr[k++] = left_arr[i];

    for ( ; j < n2; j++)
        arr[k++] = right_arr[j];

    printf("arr(%d:%d): ", left, right);
    print_array(arr, left, right + 1);
    printf("\n");
}

void merge_sort(int* arr, const int left, const int right, int (*comp)(const int, const int))
{
    if (left < right) 
    {
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid, comp);
        merge_sort(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}


int main(void)
{
    int arr[] = { 3, 4, 2, 1, 7, 5, 8, 9, 0, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("arr: ");
    print_array(arr, 0, n);
    printf("\n");

    merge_sort(arr, 0, n - 1, compare);

    printf("arr: ");
    print_array(arr, 0, n);
    printf("\n");

    return 0;
}


void print_array(const int *arr, const int start, const int end)
{
    for (int i = start; i < end; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}
