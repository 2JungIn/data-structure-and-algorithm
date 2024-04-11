#include "../include/map.h"

#include <stdlib.h>
#include <string.h>


static int pair_compare(const pair *p1, const pair *p2);
static pair *pair_find(const red_black_tree *tree, void *key, int (*key_compare)(const void *, const void *));


static int pair_compare(const pair *p1, const pair *p2)
{
    return p1->compare(p1->first, p2->first);
}

static pair *pair_find(const red_black_tree *tree, void *key, int (*key_compare)(const void *, const void *))
{
    pair dummy_pair;
    memset(&dummy_pair, 0, sizeof(pair));
    dummy_pair.first = key;
    dummy_pair.compare = key_compare;

    return (pair *)red_black_tree_find(tree, &dummy_pair);
}


map *init_map(
    int (*key_compare)(const void *, const void *),
    void (*free_key)(void *),
    void (*free_value)(void *))
{
    if (key_compare == NULL)    /* error: invalid arg */
        return NULL;

    if (free_key == NULL)    /* error: invalid arg */
        return NULL;

    if (free_value == NULL)    /* error: invalid arg */
        return NULL;
    
    map *m = NULL;
    if ((m = (map *)malloc(sizeof(map))) == NULL)    /* error: malloc() */
        return NULL;
    
    m->bucket = init_red_black_tree(
        (void (*)(void *))destroy_pair, 
        (int (*)(const void *, const void *))pair_compare
    );
        
    /* entry */
    m->key_compare = key_compare;
    m->free_key = free_key;
    m->free_value = free_value;

    return m;
}

void destroy_map(map *m)
{
    if (m == NULL)    /* error: invalid arg */
        return ;
    
    destroy_red_black_tree(m->bucket);
    free(m);
}


int map_empty(const map *m)
{
    if (m == NULL)    /* error: invalid arg */
        return -1;

    return red_black_tree_empty(m->bucket);
}

int map_size(const map *m)
{
    if (m == NULL)    /* error: invalid arg */
        return -1;

    return red_black_tree_size(m->bucket);
}


int map_insert(map *m, void *key, void *value)
{
    if (m == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;
    
    if (value == NULL)  /* error: invalid arg */
        return -1;

    pair *exisist = pair_find(m->bucket, key, m->key_compare);
    if (exisist)
        return -1;

    return red_black_tree_insert(m->bucket, init_pair(key, value, m->key_compare, m->free_key, m->free_value));
}

int map_update(map *m, void *key, void *value)
{
    if (m == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;
    
    if (value == NULL)  /* error: invalid arg */
        return -1;

    pair *exisist = pair_find(m->bucket, key, m->key_compare);
    if (!exisist)
        return -1;

    exisist->free_second(exisist->second);
    exisist->second = value;

    return 0;
}

int map_delete(map *m, void *key)
{
    if (m == NULL)    /* error: invalid arg */
        return -1;
    
    if (key == NULL)  /* error: invalid arg */
        return -1;

    pair dummy_pair;
    memset(&dummy_pair, 0, sizeof(pair));
    dummy_pair.first = key;
    dummy_pair.compare = m->key_compare;

    if (red_black_tree_delete(m->bucket, &dummy_pair) < 0)   /* delete fail */
        return -1;
    
    return 0;   /* delete success */
}


pair *map_get(map *m, void *key)
{
    if (m == NULL)   /* error: invalid arg */
        return NULL;
    
    if (key == NULL)  /* error: invalid arg */
        return NULL;

    return pair_find(m->bucket, key, m->key_compare);
}

void *map_get_key(map *m, void *key)
{
    pair *p = map_get(m, key);
    
    if (p == NULL)  /* not found */
        return NULL;
    
    return p->first;
}

void *map_get_value(map *m, void *key)
{
    pair *p = map_get(m, key);

    if (p == NULL)  /* not found */
        return NULL;
    
    return p->second;
}


void map_clear(map *m)
{
    if (m == NULL)    /* error: invalid arg */
        return ;
    
    red_black_tree_clear(m->bucket);
}


/* iterator */
iterator map_begin(const map *m)
{
    if (m == NULL)  /* error: invalid arg */
        return NULL;

    return red_black_tree_begin(m->bucket);
}

iterator map_next(const iterator iter)
{
    if (iter == NULL)   /* error: invalid arg */
        return NULL;

    return red_black_tree_next(iter);
}

iterator map_end(const map *m)
{
    if (m == NULL)  /* error: invalid arg */
        return NULL;
    
    return red_black_tree_end(m->bucket);
}

pair *map_iter_get(const iterator iter)
{
    if (iter == NULL)   /* error: invalid arg */
        return NULL;
    
    return (pair *)red_black_tree_iter_get(iter);
}

void *map_iter_get_key(const iterator iter)
{
    pair *p = map_iter_get(iter);
    
    if (p == NULL)  /* not found */
        return NULL;
    
    return p->first;
}

void *map_iter_get_value(const iterator iter)
{
    pair *p = map_iter_get(iter);
    
    if (p == NULL)  /* not found */
        return NULL;
    
    return p->second;
}
