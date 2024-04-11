#ifndef _D_LIST_H_
#define _D_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct double_linked_list
{
    int count;
    
    struct node *head;
    struct node *tail;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
} double_linked_list;
typedef struct node *iterator;

double_linked_list *init_double_linked_list(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_double_linked_list(double_linked_list *list);

int double_linked_list_empty(const double_linked_list *list);
int double_linked_list_size(const double_linked_list *list);

/* get */
void *double_linked_list_front(const double_linked_list *list);
void *double_linked_list_back(const double_linked_list *list);
void *double_linked_list_at(const double_linked_list *list, const int idx);
void *double_linked_list_find_item(const double_linked_list *list, const void *item);
int double_linked_list_find_index(const double_linked_list *list, const void *item);

int double_linked_list_reverse(double_linked_list *list);

/* insert */
int double_linked_list_insert_front(double_linked_list *list, void *item);
int double_linked_list_insert_back(double_linked_list *list, void *item);
int double_linked_list_insert_at(double_linked_list *list, const int idx, void *item);

/* delete */
void *double_linked_list_delete_front(double_linked_list *list);
void *double_linked_list_delete_back(double_linked_list *list);
void *double_linked_list_delete_at(double_linked_list *list, const int idx);
void *double_linked_list_delete(double_linked_list *list, const void *item);

void double_linked_list_clear(double_linked_list *list);

/* iterator */
iterator double_linked_list_begin(const double_linked_list *list);
iterator double_linked_list_next(const iterator iter);
iterator double_linked_list_end(const double_linked_list *list);
void *double_linked_list_iter_get(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _D_LIST_H_ */