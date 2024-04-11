#ifndef _GRAPH_H_
#define _GRAPH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "map.h"
#include "avl-tree.h"

typedef map graph;

graph *init_graph(int (*vertex_compare)(const void *, const void *), void (*free_vertex)(void *));
void destroy_graph(graph *g);

int graph_empty(const graph *g);
int graph_size(const graph *g);

int graph_insert(graph *g, void *vertex);
int graph_delete(graph *g, void *vertex);
int graph_add_edge(graph *g, void *vertex, void *edge);
int graph_del_edge(graph *g, void *vertex, void *edge);
avl_tree *graph_get_edges(graph *g, void *vertex);

void graph_clear(graph *g);

/* iterator */
iterator graph_begin(const graph *g);
iterator graph_next(const iterator iter);
iterator graph_end(const graph *m);
pair *graph_iter_get(const iterator iter);
void *graph_iter_get_vertex(const iterator iter);
void *graph_iter_get_edges(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _GRAPH_H_ */