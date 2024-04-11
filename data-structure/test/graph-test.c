#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/graph.h"
#include "../include/queue.h"
#include "../include/stack.h"

int vertex_compare(const int *key1, const int *key2);
void free_vertex(int *key);

void print_graph(const graph *g);

int *new_int(int n);

void DFS(graph *g, int v, int *visits)
{
    visits[v] = 1;
    printf("[%d] ", v);

    avl_tree *edges = graph_get_edges(g, &v);
    
    iterator begin = avl_tree_begin(edges);
    iterator end = avl_tree_end(edges);
    for (iterator itr = begin; itr != end; itr = avl_tree_next(itr))
    {
        int *w = (int *)avl_tree_iter_get(itr);
        if (visits[*w] == 0)
            DFS(g, *w, visits);
    }
}

void BFS(graph *g, int v, int *visits)
{
    queue *q = init_queue(NULL);
    
    queue_enqueue(q, &v);
    visits[v] = 1;
    
    while (!queue_empty(q))
    {
        v = *(int *)queue_front(q);
        queue_dequeue(q);

        printf("[%d] ", v);
        avl_tree *edges = graph_get_edges(g, &v);
        
        iterator begin = avl_tree_begin(edges);
        iterator end = avl_tree_end(edges);
        for (iterator itr = begin; itr != end; itr = avl_tree_next(itr))
        {
            int *w = (int *)avl_tree_iter_get(itr);
            if (visits[*w] == 0)
            {
                visits[*w] = 1;
                queue_enqueue(q, w);
            }
        }
    }

    destroy_queue(q);
}

void DFS_iter(graph *g, int v, int *visits)
{
    stack *s = init_stack(NULL);
    
    stack_push(s, &v);
    while(!stack_empty(s))
    {
        v = *(int *)stack_top(s);
        stack_pop(s);

        if (visits[v] == 0)
        {
            printf("[%d] ", v);
            visits[v] = 1;

            avl_tree *edges = graph_get_edges(g, &v);
        
            iterator begin = avl_tree_begin(edges);
            iterator end = avl_tree_end(edges);
            for (iterator itr = begin; itr != end; itr = avl_tree_next(itr))
            {
                int *w = (int *)avl_tree_iter_get(itr);
                stack_push(s, w);
            }
        }
    }

    destroy_stack(s);
}


int main(void)
{
    graph *g = init_graph(
        (int (*)(const void *, const void *))vertex_compare,
        (void (*)(void *))free_vertex
    );

    for (int i = 0; i < 7; i++)
        graph_insert(g, new_int(i));

    int vertex, edge;
    vertex  = 0;    edge = 2;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 0;    edge = 1;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 1;    edge = 4;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 1;    edge = 3;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 2;    edge = 4;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 3;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 4;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 5;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    print_graph(g);
    graph_clear(g);

    for (int i = 0; i < 7; i++)
        graph_insert(g, new_int(i));
    
    vertex  = 0;    edge = 2;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 0;    edge = 1;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 1;    edge = 4;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 1;    edge = 3;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 2;    edge = 4;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 3;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 4;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    vertex  = 5;    edge = 6;   graph_add_edge(g, &vertex, &edge);  graph_add_edge(g, &edge, &vertex);
    print_graph(g);
    
    int visits[7] = { 0 };

    printf("DFS(): ");
    memset(visits, 0, sizeof(visits));
    DFS(g, 0, visits); /* 0번 부터 방문 */
    printf("\n");

    printf("BFS(): ");
    memset(visits, 0, sizeof(visits));
    BFS(g, 0, visits); /* 0번 부터 방문 */
    printf("\n");

    printf("DFS_iter(): ");
    memset(visits, 0, sizeof(visits));
    DFS_iter(g, 0, visits); /* 0번 부터 방문 */
    printf("\n");

    vertex = 0;
    graph_delete(g, &vertex);
    print_graph(g);

    destroy_graph(g);

    return 0;
}


int vertex_compare(const int *key1, const int *key2)
{
    return (*key1) - (*key2);
}

void free_vertex(int *key)
{
    free(key);
}


void print_graph(const graph *g)
{
    printf("graph size: %d\n", graph_size(g));

    iterator bucket_begin = red_black_tree_begin(g->bucket);
    iterator bucket_end = red_black_tree_end(g->bucket);

    for (iterator bucket_itr = bucket_begin; bucket_itr != bucket_end; bucket_itr = red_black_tree_next(bucket_itr))
    {
        pair *p = (pair *)red_black_tree_iter_get(bucket_itr);

        printf("key: %d value: ", *(int *)p->first);
        iterator edges_begin = avl_tree_begin((struct avl_tree *)p->second);
        iterator edges_end = avl_tree_end((struct avl_tree *)p->second);
        
        for (iterator edge_itr = edges_begin; edge_itr != edges_end; edge_itr = avl_tree_next(edge_itr))
            printf("[%d] ", *(int *)avl_tree_iter_get(edge_itr));

        printf("\n");
    }

    printf("\n");
}

int *new_int(int n)
{
    return (int *)memcpy((int *)malloc(sizeof(int)), &n, sizeof(int));
}