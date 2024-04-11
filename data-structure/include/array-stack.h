#ifndef _ARRAY_STACK_H_
#define _ARRAY_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct array_stack 
{
    int capacity;

    void **memory;
    int top;

    void (*free_item)(void *);
} array_stack;

array_stack *init_array_stack(void (*free_item)(void *));
void destroy_array_stack(array_stack *s);
void array_stack_print(const array_stack *s, void (*print_func)(const void *));

int array_stack_full(const array_stack *s);
int array_stack_empty(const array_stack *s);
int array_stack_size(const array_stack *s);
int array_stack_resize(array_stack *s, const int size);

void *array_stack_top(const array_stack *s);
void array_stack_push(array_stack *s, void *item);
void *array_stack_pop(array_stack *s);
void array_stack_clear(array_stack *s);

#ifdef __cplusplus
}
#endif

#endif  /* _ARRAY_STACK_H_ */