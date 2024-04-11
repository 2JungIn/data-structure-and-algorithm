#include "../include/vector.h"
#include <stdlib.h>


const static int default_capacity = 15;


vector *init_vector(const int size, void (*free_item)(void *))
{
    vector *new_vector = NULL;
    if ((new_vector = (vector *)malloc(sizeof(vector))) == NULL) /* error: malloc() */
        return NULL;
    
    int capacity = default_capacity;    /* default_capacity = 15 */

    if (capacity < size)
        capacity = size * 2;
    
    if ((new_vector->memory = (void **)malloc(sizeof(void *) * capacity)) == NULL)   /* error: malloc() */
    {
        free(new_vector);
        return NULL;
    }

    new_vector->capacity = capacity;
    new_vector->count = 0;

    new_vector->free_item = free_item;

    return new_vector;
}

void destroy_vector(vector *v)
{
    if (v == NULL)    /* error: invalid arg */
        return ;
    
    vector_clear(v);
    free(v->memory);
    free(v);
}

void print_vector(const vector *v, void (*print_func)(const void *))
{
    if (v == NULL)  /* error: invalid arg */
        return ;

    if (print_func == NULL)
        return ;

    for (int i = 0; i < vector_size(v); i++)
        print_func(v->memory[i]);
}


int vector_empty(const vector *v)
{
    if (v == NULL)   /* error: invalid arg */
        return -1;

    return vector_size(v) == 0;
}

int vector_size(const vector *v)
{
    if (v == NULL)   /* error: invalid arg */
        return -1;

    return v->count;
}

int vector_resize(vector *v, const int size)
{
    if (v == NULL)   /* error: invalid arg */
        return -1;

    if (size <= 0)   /* error: size는 0보다 커야 한다. */
        return -1;

    int new_capacity = size;
    void **new_memory = NULL;
    if ((new_memory = (void **)malloc(sizeof(void *) * new_capacity)) == NULL)  /* error: malloc() */
        return -1;

    if (new_capacity < v->capacity)
    {
        int i = 0;
        for ( ; i < size; i++)
            new_memory[i] = v->memory[i];

        void (*free_item)(void *) = v->free_item;
        if (free_item)
        {
            for ( ; i < v->count; i++)
                free_item(v->memory[i]);
        }

        v->count = size;
    }
    else
    {
        for (int i = 0; i < v->count; i++)
            new_memory[i] = v->memory[i];
    }

    free(v->memory);
    v->capacity = new_capacity;
    v->memory = new_memory;

    return 0;
}

void vector_swap(vector *v, const int a, const int b)
{
    if (a < 0 || a >= vector_size(v))   /* error: index out of range */
        return ;
    if (b < 0 || b >= vector_size(v))   /* error: index out of range */
        return ;
    
    void *temp = v->memory[a];
    v->memory[a] = v->memory[b];
    v->memory[b] = temp;
}


void *vector_get_at(const vector *v, const int idx)
{
    if (v == NULL)   /* error: invalid arg */
        return NULL;
    
    if (idx < 0 || idx >= vector_size(v))   /* error: index out of range */
        return NULL;

    return v->memory[idx];
}

void vector_set_at(vector *v, const int idx, void *item)
{
    if (v == NULL)   /* error: invalid arg */
        return ;
    
    if (idx < 0 || idx >= vector_size(v))   /* error: index out of range */
        return ;

    if(item == NULL)    /* error: invalid arg */
        return ;

    v->free_item(v->memory[idx]);
    v->memory[idx] = item;
}


void *vector_back(const vector *v)
{
    if (v == NULL)   /* error: invalid arg */
        return NULL;

    if (vector_empty(v))
        return NULL;
        
    return v->memory[vector_size(v) - 1];
}


void vector_push_back(vector *v, void *item)
{
    if (v == NULL)  /* error: invalid arg */
        return ;

    if (item == NULL)   /* error: invalid arg */
        return ;
    
    if (v->capacity == v->count)
        vector_resize(v, v->capacity * 2);

    v->memory[v->count++] = item;
}

void *vector_pop_back(vector *v)
{
    if (v == NULL)   /* error: invalid arg */
        return NULL;

    if (vector_empty(v))
        return NULL;

    void *ret_item = NULL;
    
    void (*free_item)(void *) = v->free_item;
    if (free_item)
        free_item(v->memory[--(v->count)]);
    else
        ret_item = v->memory[--(v->count)];

    return ret_item;
}


void vector_insert_at(vector *v, const int idx, void *item)
{
    if (v == NULL)   /* error: invalid arg */
        return ;

    if (idx < 0 || idx >= vector_size(v))    /* error: index out of range */
        return ;

    if (item == NULL)   /* error: invalid arg */
        return ;

    if (v->capacity == v->count)
        vector_resize(v, v->capacity * 2);

    for (int i = v->count++; i > idx; i--)
        v->memory[i] = v->memory[i - 1];

    v->memory[idx] = item;
}

void *vector_delete_at(vector *v, const int idx)
{
    if (v == NULL)   /* error: invalid arg */
        return NULL;

    if (idx < 0 || idx >= vector_size(v))    /* error: index out of range */
        return NULL;

    void *ret_item = NULL;

    void (*free_item)(void *) = v->free_item;
    if (free_item)
        free_item(v->memory[idx]);
    else
        ret_item = v->memory[idx];

    v->count--;
    for (int i = idx; i < v->count; i++)
        v->memory[i] = v->memory[i + 1];

    return ret_item;
}


void vector_clear(vector *v)
{
    if (v == NULL)   /* error: invalid arg */
        return ;
    
    if (vector_empty(v))
        return ;

    void (*free_item)(void *) = v->free_item;
    if (free_item)
    {
        for (int i = 0; i < vector_size(v); i++)
            free_item(v->memory[i]);
    }
    
    v->count = 0;
}


void vector_right_shift(vector *v)
{
    if (v == NULL)  /* error: invalid arg */
        return ;

    int i = vector_size(v) - 1;
    void *temp = v->memory[i];

    while (i > 0)
    {
        v->memory[i] = v->memory[i - 1];
        i--;
    }

    v->memory[i] = temp;
}

void vector_left_shift(vector *v)
{
    if (v == NULL)  /* error: invalid arg */
        return ;

    int i = 0;
    void *temp = v->memory[i];

    while (i < vector_size(v) - 1)
    {
        v->memory[i] = v->memory[i + 1];
        i++;
    }

    v->memory[i] = temp;
}

void vector_reverse(vector *v)
{
    if (v == NULL)  /* error: invalid arg */
        return ;
    
    int left = 0;
    int right = vector_size(v) - 1;

    while (left < right)
    {
        /* swap */
        void *temp = v->memory[left];
        v->memory[left] = v->memory[right];
        v->memory[right] = temp;

        left++;
        right--;
    }
}
