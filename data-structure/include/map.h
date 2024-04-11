#ifndef _MAP_H_
#define _MAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "pair.h"
#include "red-black-tree.h"

typedef struct map
{
    red_black_tree *bucket;

    /* struct entry */
    int (*key_compare)(const void *, const void *);
    void (*free_key)(void *);
    void (*free_value)(void *);
} map;
typedef struct node *iterator;


map *init_map(
    int (*key_compare)(const void *, const void *),
    void (*free_key)(void *),
    void (*free_value)(void *));
void destroy_map(map *m);

int map_empty(const map *m);
int map_size(const map *m);

int map_insert(map *m, void *key, void *value);
int map_update(map *m, void *key, void *value);
int map_delete(map *m, void *key);
pair *map_get(map *m, void *key);
void *map_get_key(map *m, void *key);
void *map_get_value(map *m, void *key);

void map_clear(map *m);

/* iterator */
iterator map_begin(const map *m);
iterator map_next(const iterator iter);
iterator map_end(const map *m);
pair *map_iter_get(const iterator iter);
void *map_iter_get_key(const iterator iter);
void *map_iter_get_value(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _MAP_H_ */