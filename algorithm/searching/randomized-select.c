/**
 * randomized-select.c
 *  
 * randomized partition을 사용해서 arr가 정렬 되었을 때,
 * k - 1 번째 값을 가져오는 프로그램입니다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);
void print_array(const int *arr, const int n, const int lo, const int hi);


int partition(int *arr, const int lo, const int hi)
{
    int pivot = arr[hi];
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

int randomized_partition(int *arr, const int lo, const int hi)
{
    int random = lo + (rand() % (hi - lo + 1));
    
    swap(&arr[random], &arr[hi]);

    return partition(arr, lo, hi);
}

int randomized_select(int *arr, const int n, int lo, int hi, int k)
{
    printf("n: %d\tlo: %d\t hi: %d\tk: %d\n\n", hi - lo + 1, lo, hi, k);
    print_array(arr, n, lo, hi);
    printf("\n");

    if (lo == hi)
        return arr[lo];

    int index = randomized_partition(arr, lo, hi);

    if (index - lo < k - 1)
        return randomized_select(arr, n, index + 1, hi, k - index + lo - 1);
    else if (index - lo > k - 1)
        return randomized_select(arr, n, lo, index - 1, k);
    else    /* index - lo == k - 1 */
        return arr[index];
    
    return -1;   /* error */
}


int main(void)
{
    srand(time(NULL));
    
    int arr[] = { 9, 8, 7, 6, 4, 3, 2, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", randomized_select(arr, n, 0, n - 1, n / 2));

    return 0;
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(const int *arr, const int n, const int lo, const int hi)
{
    printf("index:    ");
    for (int i = 0; i < n; i++)
        printf("%d ", i);
    printf("\n");

    printf("array:    ");
    for (int i = 0; i < n; i++)
    {
        if (i >= lo && i <= hi)
            printf("%d ", arr[i]);
        else
            printf("  ");
    }
    
    printf("\n");
}
