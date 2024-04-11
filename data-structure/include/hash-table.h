#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "single-linked-list.h"

typedef struct hash_table
{
    int capacity;

    int count;

    single_linked_list **bucket;

    int (*hash_func)(const void *);

    /* struct entry */
    int (*key_compare)(const void *, const void *);
    void (*free_key)(void *);
    void (*free_value)(void *);
} hash_table;


hash_table *init_hash_table(
    int size,
    int (*hash_func)(const void *), 
    int (*key_compare)(const void *, const void *),
    void (*free_key)(void *),
    void (*free_value)(void *));
void destroy_hash_table(hash_table *h_table);

int hash_table_empty(const hash_table *h_table);
int hash_table_size(const hash_table *h_table);

int hash_table_insert(hash_table *h_table, void *key, void *value);
int hash_table_update(hash_table *h_table, void *key, void *value);
int hash_table_delete(hash_table *h_table, void *key);
void *hash_table_get_key(hash_table *h_table, void *key);
void *hash_table_get_value(hash_table *h_table, void *key);

void hash_table_clear(hash_table *h_table);

#ifdef __cplusplus
}
#endif

#endif  /* _HASH_TABLE_H_ */