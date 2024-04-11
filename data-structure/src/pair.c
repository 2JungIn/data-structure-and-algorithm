#include "../include/pair.h"
#include <stdlib.h>

pair *init_pair(void *first, void *second, int (*compare)(const void *, const void *), void (*free_first)(void *), void (*free_second)(void *))
{
    if (first == NULL)  /* error: invalid arg */
        return NULL;

    if (second == NULL) /* error: invalid arg */
        return NULL;
    
    pair *p = NULL;
    if ((p = (pair *)malloc(sizeof(pair))) == NULL)   /* error: malloc() */
        return NULL;

    p->first = first;
    p->second = second;

    p->compare = compare;

    p->free_first = free_first;
    p->free_second = free_second;

    return p;
}

void destroy_pair(pair *p)
{
    if (p == NULL)   /* error: invalid arg */
        return ;

    void (*free_func)(void *) = NULL;
    
    /* first element free */
    free_func = p->free_first;
    if (free_func)
        free_func(p->first);

    /* second element free */
    free_func = p->free_second;
    if (free_func)
        free_func(p->second);

    free(p);
}


void *get_first(const pair *p)
{
    if (p == NULL)   /* error: invalid arg */
        return NULL;

    return p->first;
}

void *get_second(const pair *p)
{
    if (p == NULL)   /* error: invalid arg */
        return NULL;

    return p->second;
}

int set_first(pair *p, void *elem)
{
    if (p == NULL)  /* error: invalid arg */
        return -1;

    if (elem == NULL)   /* error: invalid arg */
        return -1;

    void (*free_first)(void *) = p->free_first;
    if (free_first)
        free_first(p->first);

    p->first = elem;

    return 0;
}

int set_second(pair *p, void *elem)
{
    if (p == NULL)  /* error: invalid arg */
        return -1;
        
    if (elem == NULL)   /* error: invalid arg */
        return -1;
    
    void (*free_second)(void *) = p->free_second;
    if (free_second)
        free_second(p->second);

    p->second = elem;

    return 0;
}


void swap_elem(pair *p, int (*compare)(const void *, const void *))
{
    if(p == NULL)   /* error: invalid arg */
        return ;

    /* element swap */
    void *temp_item = p->first;
    p->first = p->second;
    p->second = temp_item;

    /* free function swap */
    void (*free_func)(void *) = p->free_first;
    p->free_first = p->free_second;
    p->free_second = free_func;

    if (compare)
        p->compare = compare;
}
