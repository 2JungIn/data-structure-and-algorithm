#include "../include/graph.h"
#include <stdlib.h>


static void free_value(avl_tree *avl_tree)
{
    if (avl_tree == NULL)
        return ;

    destroy_avl_tree(avl_tree);
}


graph *init_graph(int (*vertex_compare)(const void *, const void *), void (*free_vertex)(void *))
{
    return init_map(vertex_compare, free_vertex, (void (*)(void *))free_value);
}

void destroy_graph(graph *g)
{
    destroy_map(g);
}


int graph_empty(const graph *g)
{
    return map_empty(g);
}

int graph_size(const graph *g)
{
    return map_size(g);
}


int graph_insert(graph *g, void *vertex)
{
    if (g == NULL)  /* error: invalid arg */
        return -1;
    
    if (vertex == NULL) /* error: invalid arg */
        return -1;
    
    return map_insert(g, vertex, init_avl_tree(NULL, g->key_compare));
}

int graph_delete(graph *g, void *vertex)
{
    if (g == NULL)  /* error: invalid arg */
        return -1;
    
    if (vertex == NULL) /* error: invalid arg */
        return -1;
    
    iterator m_begin = map_begin(g);
    iterator m_end = map_end(g);
    for (iterator m_itr = m_begin; m_itr != m_end; m_itr = map_next(m_itr))
        avl_tree_delete(map_iter_get_value(m_itr), vertex);

    return map_delete(g, vertex);
}

int graph_add_edge(graph *g, void *vertex, void *edge)
{
    if (g == NULL)  /* error: invalid arg */
        return -1;

    if (vertex == NULL) /* error: invalid arg */
        return -1;
    
    if (edge == NULL)   /* error: invalid arg */
        return -1;

    return avl_tree_insert(graph_get_edges(g, vertex), map_get_key(g, edge));
}

int graph_del_edge(graph *g, void *vertex, void *edge)
{
    if (g == NULL)  /* error: invalid arg */
        return -1;

    if (vertex == NULL) /* error: invalid arg */
        return -1;
    
    if (edge == NULL)   /* error: invalid arg */
        return -1;

    return avl_tree_delete(graph_get_edges(g, vertex), map_get_key(g, edge));
}

avl_tree *graph_get_edges(graph *g, void *vertex)
{
    if (g == NULL)  /* error: invalid arg */
        return NULL;

    if (vertex == NULL) /* error: invalid arg */
        return NULL;

    return (avl_tree *)map_get_value(g, vertex);
}


void graph_clear(graph *g)
{
    map_clear(g);
}


/* iterator */
iterator graph_begin(const graph *g)
{
    return map_begin(g);
}

iterator graph_next(const iterator iter)
{
    return map_next(iter);
}

iterator graph_end(const graph *g)
{
    return map_end(g);
}

pair *graph_iter_get(const iterator iter)
{
    return map_iter_get(iter);
}

void *graph_iter_get_vertex(const iterator iter)
{
    return map_iter_get_key(iter);
}

void *graph_iter_get_edges(const iterator iter)
{
    return map_iter_get_value(iter);
}
