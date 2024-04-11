#ifndef _S_LIST_H_
#define _S_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct single_linked_list
{
    int count;
    
    struct node *head;
    struct node *tail;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
} single_linked_list;
typedef struct node *iterator;


single_linked_list *init_single_linked_list(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_single_linked_list(single_linked_list *list);


int single_linked_list_empty(const single_linked_list *list);
int single_linked_list_size(const single_linked_list *list);


void *single_linked_list_front(const single_linked_list *list);
void *single_linked_list_back(const single_linked_list *list);
void *single_linked_list_at(const single_linked_list *list, const int idx);

/* search */
void *single_linked_list_find_item(const single_linked_list *list, const void *item);
int single_linked_list_find_index(const single_linked_list *list, const void *item);

int single_linked_list_reverse(single_linked_list *list);

/* insert */
int single_linked_list_insert_front(single_linked_list *list, void *item);
int single_linked_list_insert_back(single_linked_list *list, void *item);
int single_linked_list_insert_at(single_linked_list *list, const int idx, void *item);

/* delete */
void *single_linked_list_delete_front(single_linked_list *list);
void *single_linked_list_delete_back(single_linked_list *list);
void *single_linked_list_delete_at(single_linked_list *list, const int idx);
void *single_linked_list_delete(single_linked_list *list, const void *item);

void single_linked_list_clear(single_linked_list *list);

/* iterator */
iterator single_linked_list_begin(const single_linked_list *list);
iterator single_linked_list_next(const iterator iter);
iterator single_linked_list_end(const single_linked_list *list);
void *single_linked_list_iter_get(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _S_LIST_H_ */