#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pair.h"

int main(void)
{
    int *first = (int *)malloc(sizeof(int));
    char *second = (char *)malloc(sizeof(char) * 30);
    
    *first = 10;
    strcpy(second, "hello world!");

    printf("*** make_pair(10, \"hello world\") & get_first() & get_second() ***\n");
    pair *p = init_pair(first, second, NULL, free, free);

    printf("first: %d second: %s\n", *(int *)get_first(p), (char *)get_second(p));
    printf("*****************************************************************\n\n");

    printf("********** set_first(123) & set_second(\"new second\") ************\n");
    int *new_first = (int *)malloc(sizeof(int));
    char *new_second = (char *)malloc(sizeof(char) * 30);
    
    *new_first = 123;
    strcpy(new_second, "new second");

    set_first(p, new_first);
    set_second(p, new_second);
    printf("first: %d second: %s\n", *(int *)get_first(p), (char *)get_second(p));
    printf("*****************************************************************\n\n");

    printf("************************** swap_elem() **************************\n");
    swap_elem(p, NULL);
    printf("first: %s second: %d\n", (char *)p->first, *(int *)p->second);
    printf("*****************************************************************\n\n");

    destroy_pair(p);

    return 0;
}