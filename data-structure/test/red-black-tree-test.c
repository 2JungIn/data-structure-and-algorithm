#include "../include/red-black-tree.h"
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

void print(const red_black_tree *red_black_tree)
{
    printf("red black tree size: %d\n", red_black_tree_size(red_black_tree));
    
    iterator begin = red_black_tree_begin(red_black_tree);
    iterator end = red_black_tree_end(red_black_tree);

    for (iterator itr = begin; itr != end; itr = red_black_tree_next(itr))
    {
        int *data = (int *)red_black_tree_iter_get(itr);
        printf("[%d] ", *data);
    }

    printf("\n");
}

int main(void)
{
    red_black_tree *rb_tree = init_red_black_tree(free, comp);

    red_black_tree_insert(rb_tree, new_data(1));
    red_black_tree_insert(rb_tree, new_data(3));
    red_black_tree_insert(rb_tree, new_data(2));

    red_black_tree_preorder(rb_tree, work);
    printf("\n");

    red_black_tree_inorder(rb_tree, work);
    printf("\n");

    red_black_tree_postorder(rb_tree, work);
    printf("\n");

    print(rb_tree);

    red_black_tree_clear(rb_tree);

    red_black_tree_insert(rb_tree, new_data(3));
    red_black_tree_insert(rb_tree, new_data(1));
    red_black_tree_insert(rb_tree, new_data(2));

    red_black_tree_preorder(rb_tree, work);
    printf("\n");

    red_black_tree_inorder(rb_tree, work);
    printf("\n");

    red_black_tree_postorder(rb_tree, work);
    printf("\n");

    print(rb_tree);

    red_black_tree_clear(rb_tree);

    for (int i = 1; i <= 15; i++)
        red_black_tree_insert(rb_tree, new_data(i));

    printf("min: %d\n", *(int *)red_black_tree_min(rb_tree));
    printf("max: %d\n", *(int *)red_black_tree_max(rb_tree));

    red_black_tree_preorder(rb_tree, work);
    printf("\n");

    red_black_tree_inorder(rb_tree, work);
    printf("\n");

    red_black_tree_postorder(rb_tree, work);
    printf("\n");

    print(rb_tree);

    printf("min: %d\n", *(int *)red_black_tree_min(rb_tree));
    printf("max: %d\n", *(int *)red_black_tree_max(rb_tree));

    int *data = new_data(0);
    red_black_tree_delete(rb_tree, data);

    red_black_tree_inorder(rb_tree, work);
    printf("\n");

    int *result = NULL;

    *data = 4;
    result = red_black_tree_find(rb_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    *data = 9999;
    result = red_black_tree_find(rb_tree, data);
    if (result == NULL)
        printf("%d is not found!\n", *data);
    else
        printf("%d is found!\n", *data);

    for (int i = 1; i <= 15; i++)
    {
        *data = i;
        printf("%d (height: %d)\n", i, red_black_tree_height(rb_tree, data));

        red_black_tree_delete(rb_tree, data);
        print(rb_tree);
    }
    
    free(data);

    destroy_red_black_tree(rb_tree);

    return 0;
}