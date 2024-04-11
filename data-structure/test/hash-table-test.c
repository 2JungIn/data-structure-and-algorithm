#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "../include/pair.h"
#include "../include/hash-table.h"

#define OFFSET 96           /* 'a' - 1 = 97 - 1 = 96*/
#define R      31
#define M      1234567891


int hash_function(const char *key)
{
    const size_t key_count = strlen(key);

    uint64_t hash_value = 0;
    uint64_t r = 1;

    for (size_t i = 0; i < key_count; i++)
    {
        int unique_number = key[i] - OFFSET;    // 1 ~ 26
        hash_value = (hash_value + (unique_number * r)) % M;  // (A + B) MOD M = ((A MOD M) + (B MOD M)) MOD M
        r = (r * R) % M;  // (A x B) MOD M = ((A MOD M) x (B MOD M)) MOD M 
    }
    
    // hash_value = 0; /* hash collision test */

    return (hash_value >> 32) ^ (hash_value);
}

int key_compare(const char *key1, const char *key2)
{
    return strcmp(key1, key2);
}

void free_key(char *key)
{
    free(key);
}

void free_value(char *value)
{
    free(value);
}


void print_hash_table(const hash_table *h_table)
{
    printf("hash table size: %d\n", hash_table_size(h_table));
    
    int capacity = h_table->capacity;
    single_linked_list **bucket = h_table->bucket;
    for (int i = 0; i < capacity; i++)
    {
        if (bucket[i])
        {
            printf("index: %d\n", i);
            iterator list_begin = single_linked_list_begin(bucket[i]);
            iterator list_end = single_linked_list_end(bucket[i]);

            for (iterator itr = list_begin; itr != list_end; itr = single_linked_list_next(itr))
            {
                pair *p = single_linked_list_iter_get(itr);

                printf("key: %s value: %s\n", (char *)p->first, (char *)p->second);
            }

            printf("\n");
        }
    }

    printf("\n");
}

int main(void)
{
    char file_name[] = "hello";
    int hash_value = hash_function(file_name);
    printf("hash value: %d\n", hash_value);

    hash_table *h_table = init_hash_table(
        0,
        (int (*)(const void *))hash_function,
        (int (*)(const void *, const void *))key_compare,
        (void (*)(void *))free_key,
        (void (*)(void *))free_value
    );

    hash_table_insert(h_table, strdup("userA"), strdup("hello"));
    hash_table_insert(h_table, strdup("userB"), strdup("hello"));
    hash_table_insert(h_table, strdup("userC"), strdup("hello"));
    hash_table_insert(h_table, strdup("userD"), strdup("hello"));
    hash_table_insert(h_table, strdup("userE"), strdup("hello"));
    hash_table_insert(h_table, strdup("userF"), strdup("hello"));
    hash_table_delete(h_table, "userA");
    print_hash_table(h_table);

    char *key_list[] = { "userA", "userB", "userC", "userD", "userE", "userF", NULL};
    char *result = NULL;
    for (int i = 0; key_list[i]; i++)
    {
        if ((result = (char *)hash_table_get_value(h_table, key_list[i])) == NULL)
            printf("not found!\n");
        else
            hash_table_update(h_table, key_list[i], strdup("chage!"));
    }

    print_hash_table(h_table);
    destroy_hash_table(h_table);

    return 0;
}
