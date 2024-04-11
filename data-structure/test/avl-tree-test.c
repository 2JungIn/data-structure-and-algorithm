#include "../include/avl-tree.h"
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

void print(const avl_tree *avl_tree)
{
    printf("avl tree size: %d\n", avl_tree_size(avl_tree));
    
    iterator begin = avl_tree_begin(avl_tree);
    iterator end = avl_tree_end(avl_tree);

    for (iterator itr = begin; itr != end; itr = avl_tree_next(itr))
    {
        int *data = (int *)avl_tree_iter_get(itr);
        printf("[%d] ", *data);
    }

    printf("\n");
}

int main(void)
{
    avl_tree *avl_tree = init_avl_tree(free, comp);

    avl_tree_insert(avl_tree, new_data(1));
    avl_tree_insert(avl_tree, new_data(3));
    avl_tree_insert(avl_tree, new_data(2));

    avl_tree_preorder(avl_tree, work);
    printf("\n");

    avl_tree_inorder(avl_tree, work);
    printf("\n");

    avl_tree_postorder(avl_tree, work);
    printf("\n");

    print(avl_tree);

    avl_tree_clear(avl_tree);

    avl_tree_insert(avl_tree, new_data(3));
    avl_tree_insert(avl_tree, new_data(1));
    avl_tree_insert(avl_tree, new_data(2));

    avl_tree_preorder(avl_tree, work);
    printf("\n");

    avl_tree_inorder(avl_tree, work);
    printf("\n");

    avl_tree_postorder(avl_tree, work);
    printf("\n");

    print(avl_tree);

    avl_tree_clear(avl_tree);

    for (int i = 1; i <= 15; i++)
        avl_tree_insert(avl_tree, new_data(i));

    printf("min: %d\n", *(int *)avl_tree_min(avl_tree));
    printf("max: %d\n", *(int *)avl_tree_max(avl_tree));

    avl_tree_preorder(avl_tree, work);
    printf("\n");

    avl_tree_inorder(avl_tree, work);
    printf("\n");

    avl_tree_postorder(avl_tree, work);
    printf("\n");

    print(avl_tree);

    int *data = new_data(0);
    avl_tree_delete(avl_tree, data);

    avl_tree_inorder(avl_tree, work);
    printf("\n");

    int *result = NULL;

    *data = 4;
    result = avl_tree_find(avl_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    *data = 9999;
    result = avl_tree_find(avl_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    for (int i = 1; i <= 15; i++)
    {
        *data = i;
        printf("%d (height: %d)\n", i, avl_tree_height(avl_tree, data));

        avl_tree_delete(avl_tree, data);
        print(avl_tree);
    }
    
    free(data);

    destroy_avl_tree(avl_tree);

    return 0;
}