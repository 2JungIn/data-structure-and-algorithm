#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector
{
    int capacity;
    int count;
    void **memory;

    void (*free_item)(void *);
} vector;


vector *init_vector(const int size, void (*free_item)(void *));
void destroy_vector(vector *v);
void print_vector(const vector *v, void (*print_func)(const void *));

int vector_empty(const vector *v);
int vector_size(const vector *v);
int vector_resize(vector *v, const int size);
void vector_swap(vector *v, const int a, const int b);

void *vector_get_at(const vector *v, const int idx);
void vector_set_at(vector *v, const int idx, void *item);

void *vector_back(const vector *v);

void vector_push_back(vector *v, void *item);
void *vector_pop_back(vector *v);

void vector_insert_at(vector *v, const int idx, void *item);
void *vector_delete_at(vector *v, const int idx);

void vector_clear(vector *v);

void vector_right_shift(vector *v);
void vector_left_shift(vector *v);
void vector_reverse(vector *v);

#ifdef __cplusplus
}
#endif

#endif  /* _VECTOR_H_ */