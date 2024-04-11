#include "../include/binary-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *new_data(int num)
{
    return memcpy(malloc(sizeof(int)), &num, sizeof(int));
}

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void work(void *data)
{
    printf("[%d] ", *(int *)data);
}

void print(const binary_tree *bin_tree)
{
    printf("binary tree size: %d\n", binary_tree_size(bin_tree));

    iterator begin = binary_tree_begin(bin_tree);
    iterator end = binary_tree_end(bin_tree);

    for (iterator itr = begin; itr != end; itr = binary_tree_next(itr))
    {
        int *data = (int *)binary_tree_iter_get(itr);
        printf("[%d] ", *data);
    }

    printf("\n");
}

int main(void)
{
    binary_tree *bin_tree = init_binary_tree(free, comp);

    binary_tree_insert(bin_tree, new_data(8));
    binary_tree_insert(bin_tree, new_data(4));
    binary_tree_insert(bin_tree, new_data(12));
    binary_tree_insert(bin_tree, new_data(2));
    binary_tree_insert(bin_tree, new_data(6));
    binary_tree_insert(bin_tree, new_data(10));
    binary_tree_insert(bin_tree, new_data(14));
    binary_tree_insert(bin_tree, new_data(1));
    binary_tree_insert(bin_tree, new_data(3));
    binary_tree_insert(bin_tree, new_data(5));
    binary_tree_insert(bin_tree, new_data(7));
    binary_tree_insert(bin_tree, new_data(9));
    binary_tree_insert(bin_tree, new_data(11));
    binary_tree_insert(bin_tree, new_data(13));
    binary_tree_insert(bin_tree, new_data(15));
    
    binary_tree_preorder(bin_tree, work);
    printf("\n");

    binary_tree_inorder(bin_tree, work);
    printf("\n");

    binary_tree_postorder(bin_tree, work);
    printf("\n");

    print(bin_tree);

    printf("min: %d\n", *(int *)binary_tree_min(bin_tree));
    printf("max: %d\n", *(int *)binary_tree_max(bin_tree));

    int *data = new_data(0);
    binary_tree_delete(bin_tree, data);
    print(bin_tree);

    int *result = NULL;

    *data = 4;
    result = binary_tree_find(bin_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    *data = 9999;
    result = binary_tree_find(bin_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    for (int i = 1; i <= 15; i++)
    {
        *data = i;
        printf("%d (height: %d)\n", i, binary_tree_height(bin_tree, data));

        binary_tree_delete(bin_tree, data);
        print(bin_tree);
    }
    
    free(data);

    destroy_binary_tree(bin_tree);

    return 0;
}