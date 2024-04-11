#include "../include/hash-table.h"
#include "../include/pair.h"
#include "../include/single-linked-list.h"

#include <stdlib.h>
#include <string.h>

const static int default_capacity = 15;
const static int threshold = 15;


static int pair_compare(const pair *p1, const pair *p2);
static pair *pair_find(const single_linked_list *list, void *key, int (*key_compare)(const void *, const void *));

static int hash_table_resize(hash_table *h_table);


static int pair_compare(const pair *p1, const pair *p2)
{
    return p1->compare(p1->first, p2->first);
}

static pair *pair_find(const single_linked_list *list, void *key, int (*key_compare)(const void *, const void *))
{
    pair dummy_pair;
    memset(&dummy_pair, 0, sizeof(pair));
    dummy_pair.first = key;
    dummy_pair.compare = key_compare;

    return (pair *)single_linked_list_find_item(list, &dummy_pair);
}


hash_table *init_hash_table(
    int size,
    int (*hash_func)(const void *), 
    int (*key_compare)(const void *, const void *),
    void (*free_key)(void *),
    void (*free_value)(void *))
{
    if (hash_func == NULL)    /* error: invalid arg */
        return NULL;

    if (key_compare == NULL)    /* error: invalid arg */
        return NULL;

    if (free_key == NULL)    /* error: invalid arg */
        return NULL;

    if (free_value == NULL)    /* error: invalid arg */
        return NULL;
    
    int capacity = default_capacity;    /* default_capacity = 15 */

    if (capacity < size)
        capacity = size * 2;

    hash_table *h_table = NULL;
    if ((h_table = (hash_table *)malloc(sizeof(hash_table))) == NULL)    /* error: calloc() */
        return NULL;
    
    if ((h_table->bucket = (single_linked_list **)calloc(capacity, sizeof(single_linked_list *))) == NULL)   /* error: calloc() */
    {
        free(h_table);
        return NULL;
    }
    
    h_table->capacity = capacity;

    h_table->count = 0;
    
    h_table->hash_func = hash_func;

    /* entry */
    h_table->key_compare = key_compare;
    h_table->free_key = free_key;
    h_table->free_value = free_value;

    return h_table;
}

void destroy_hash_table(hash_table *h_table)
{
    if (h_table == NULL)    /* error: invalid arg */
        return ;
    
    hash_table_clear(h_table);
    free(h_table->bucket);
    free(h_table);
}


int hash_table_empty(const hash_table *h_table)
{
    if (h_table == NULL)    /* error: invalid arg */
        return -1;

    return h_table->count == 0;
}

int hash_table_size(const hash_table *h_table)
{
    if (h_table == NULL)    /* error: invalid arg */
        return -1;

    return h_table->count;
}

static int hash_table_resize(hash_table *h_table)
{
    int new_capacity = h_table->capacity * 2;
    single_linked_list **new_bucket = NULL;
    if ((new_bucket = (single_linked_list **)calloc(new_capacity, sizeof(single_linked_list *))) == NULL)  /* error: calloc() */
        return -1;

    int (*hash_func)(const void *) = h_table->hash_func;
    single_linked_list **old_bucket = h_table->bucket;
    for (int i = 0; i < h_table->capacity; i++)
    {
        if (old_bucket[i] == NULL)
            continue;

        iterator list_begin = single_linked_list_begin(old_bucket[i]);
        iterator list_end = single_linked_list_end(old_bucket[i]);
        iterator temp = NULL;
        for (iterator itr = list_begin; itr != list_end; itr = single_linked_list_next(itr))
        {
            free(temp);

            pair *p = (pair *)single_linked_list_iter_get(itr);
            int index = hash_func(p->first) % new_capacity;
            
            if (new_bucket[index] == NULL)  /* new */
            {
                new_bucket[index] = init_single_linked_list(
                    (void (*)(void *))destroy_pair, 
                    (int (*)(const void *, const void *))pair_compare);
            }
            
            single_linked_list_insert_back(new_bucket[index], p);

            temp = itr;
        }
        
        free(temp);
        free(old_bucket[i]);
    }

    free(old_bucket);
    h_table->capacity = new_capacity;
    h_table->bucket = new_bucket;

    return 0;
}


int hash_table_insert(hash_table *h_table, void *key, void *value)
{
    if (h_table == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;
    
    if (value == NULL)  /* error: invalid arg */
        return -1;

    int index = h_table->hash_func(key) % h_table->capacity;
    single_linked_list **bucket = h_table->bucket;
    
    if (bucket[index] == NULL)  /* new */
    {
        bucket[index] = init_single_linked_list(
            (void (*)(void *))destroy_pair, 
            (int (*)(const void *, const void *))pair_compare);
    }

    pair *exisist = pair_find(bucket[index], key, h_table->key_compare);
    if (exisist)    /* hash collision */
        return -1;

    h_table->count++;
    single_linked_list_insert_back(bucket[index], init_pair(key, value, h_table->key_compare, h_table->free_key, h_table->free_value));
    
    if (h_table->count == h_table->capacity)
        return hash_table_resize(h_table);

    if (single_linked_list_size(bucket[index]) >= threshold)
        return hash_table_resize(h_table);

    return 0;
}

int hash_table_update(hash_table *h_table, void *key, void *value)
{
    if (h_table == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;
    
    if (value == NULL)  /* error: invalid arg */
        return -1;

    int index = h_table->hash_func(key) % h_table->capacity;
    single_linked_list **bucket = h_table->bucket;

    if (bucket[index] == NULL)  /* not found */
        return -1;

    pair *exisist = pair_find(bucket[index], key, h_table->key_compare);
    if (!exisist)    /* not found */
        return -1;

    exisist->free_second(exisist->second);
    exisist->second = value;

    return 0;
}

int hash_table_delete(hash_table *h_table, void *key)
{
    if (h_table == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;

    int index = h_table->hash_func(key) % h_table->capacity;
    single_linked_list **bucket = h_table->bucket;

    if (bucket[index] == NULL)  /* not found */
        return -1;

    if (single_linked_list_size(bucket[index]) == 1)
    {
        h_table->count--;
        destroy_single_linked_list(bucket[index]);
        bucket[index] = NULL;

        return 0;
    }

    pair dummy_pair;
    memset(&dummy_pair, 0, sizeof(pair));
    dummy_pair.first = key;
    dummy_pair.compare = h_table->key_compare;

    if (single_linked_list_delete(bucket[index], &dummy_pair) != NULL)
        return -1;  /* delete fail */
    
    h_table->count--;
    return 0;   /* delete success */
}



void *hash_table_get_key(hash_table *h_table, void *key)
{
    if (h_table == NULL)    /* error: invalid arg */
        return NULL;
    
    if (key == NULL)  /* error: invalid arg */
        return NULL;

    int index = h_table->hash_func(key) % h_table->capacity;
    single_linked_list **bucket = h_table->bucket;
    
    if (bucket[index] == NULL)  /* not found */
        return NULL;
    
    pair *exisist = pair_find(bucket[index], key, h_table->key_compare);
    if (!exisist)   /* not found */
        return NULL;
    
    return exisist->first;
}

void *hash_table_get_value(hash_table *h_table, void *key)
{
    if (h_table == NULL)    /* error: invalid arg */
        return NULL;
    
    if (key == NULL)  /* error: invalid arg */
        return NULL;

    int index = h_table->hash_func(key) % h_table->capacity;
    single_linked_list **bucket = h_table->bucket;
    
    if (bucket[index] == NULL)  /* not found */
        return NULL;
    
    pair *exisist = pair_find(bucket[index], key, h_table->key_compare);
    if (!exisist)   /* not found */
        return NULL;
    
    return exisist->second;
}


void hash_table_clear(hash_table *h_table)
{
    if (h_table == NULL)    /* error: invalid arg */
        return ;
    
    int capacity = h_table->capacity;
    for (int i = 0; i < capacity; i++)
    {
        single_linked_list *list = h_table->bucket[i];
        
        if (list)
            destroy_single_linked_list(list);
        
        h_table->bucket[i] = NULL;
    }
    
    h_table->count = 0;
}
