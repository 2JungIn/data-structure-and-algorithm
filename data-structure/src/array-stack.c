#include "../include/array-stack.h"
#include <stdlib.h>


const static int default_capacity = 15;


array_stack *init_array_stack(void (*free_item)(void *))
{
    array_stack *s = NULL;
    if ((s = (array_stack *)malloc(sizeof(array_stack))) == NULL)    /* error: malloc() */
        return NULL;
    
    if ((s->memory = (void **)malloc(sizeof(void *) * default_capacity)) == NULL)   /* error: malloc() */
    {
        free(s);
        return NULL;
    }

    s->capacity = default_capacity;
    s->top = -1;

    s->free_item = free_item;

    return s;
}

void destroy_array_stack(array_stack *s)
{
    if (s == NULL)    /* error: invalid arg */
        return ;
    
    array_stack_clear(s);
    free(s->memory);
    free(s);
}

void array_stack_print(const array_stack *s, void (*print_func)(const void *))
{
    if (s == NULL)  /* error: invalid arg */
        return ;

    if (print_func == NULL)
        return ;

    for (int i = 0; i < array_stack_size(s); i++)
        print_func(s->memory[i]);
}


int array_stack_full(const array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return -1;

    return s->top == s->capacity - 1;
}

int array_stack_empty(const array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return -1;

    return s->top < 0;
}

int array_stack_size(const array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return -1;

    if (array_stack_empty(s))
        return 0;

    return s->top + 1;
}

int array_stack_resize(array_stack *s, const int size)
{
    if (s == NULL)   /* error: invalid arg */
        return -1;

    if (size <= 0)   /* error: size는 0보다 커야 한다. */
        return -1;

    int new_capacity = size;
    void **new_memory = NULL;
    if ((new_memory = (void **)malloc(sizeof(void *) * new_capacity)) == NULL)  /* error: malloc() */
        return -1;

    if (new_capacity < s->capacity)
    {
        int i = 0;
        for ( ; i < size; i++)
            new_memory[i] = s->memory[i];


        void (*free_item)(void *) = s->free_item;
        if (free_item)
        {
            for ( ; i <= s->top; i++)
                free_item(s->memory[i]);
        }

        s->top = size - 1;
    }
    else
    {
        for (int i = 0; i <= s->top; i++)
            new_memory[i] = s->memory[i];
    }

    free(s->memory);
    s->capacity = new_capacity;
    s->memory = new_memory;

    return 0;
}


void *array_stack_top(const array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return NULL;

    if (array_stack_empty(s))
        return NULL;

    return s->memory[s->top];
}

void array_stack_push(array_stack *s, void *item)
{
    if (s == NULL)  /* error: invalid arg */
        return ;
    
    if (item == NULL)   /* error: invalid arg */
        return ;

    if (array_stack_full(s))
        array_stack_resize(s, s->capacity * 2);
    
    s->memory[++(s->top)] = item;
}

void *array_stack_pop(array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return NULL;
    
    if (array_stack_empty(s))
        return NULL;

    void *ret_item = NULL;
    
    void (*free_item)(void *) = s->free_item;
    if (free_item)
        free_item(s->memory[s->top]);
    else
        ret_item = s->memory[s->top];
    
    s->top--;

    return ret_item;
}


void array_stack_clear(array_stack *s)
{
    if (s == NULL)  /* error: invalid arg */
        return ;

    while (!array_stack_empty(s))
        array_stack_pop(s);

    s->top = -1;
}
