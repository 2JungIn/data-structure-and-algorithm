/**
 * lower-bound.c
 * 
 * arr[i] >= x 를 만족하는 i의 최솟값을 찾는 프로그램입니다.
**/

#include <stdio.h>

void print_array(const int *arr, const int n);


int lower_bound(const int *arr, const int n, const int x)
{
    int left = -1;
    int right = n;

    while ((left + 1) < right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] >= x)
            right = mid;
        else
            left = mid;
    }

    return right;
}


int main(void)
{
    int arr[] = { 1, 2, 2, 3, 3, 3, 4, 5, 6, 6, 7, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int x = 3;  /* find value */

    print_array(arr, n);
    printf("lower_bound(%d): %d\n", x, lower_bound(arr, n, x));

    return 0;
}


void print_array(const int *arr, const int n)
{
    printf("Index: ");
    for (int i = 0; i < n; i++)
        printf ("%2d ", i);
    printf("\n");

    printf("Value: ");
    for (int i = 0; i < n; i++)
        printf("%2d ", arr[i]);
    printf("\n");
}