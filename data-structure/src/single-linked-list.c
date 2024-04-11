#include "../include/single-linked-list.h"
#include <stdlib.h>

struct node
{
    void *item;
    struct node *next;
};


static struct node *init_node(void *item)
{
    struct node *n = NULL;
    if ((n = (struct node *)malloc(sizeof(struct node))) == NULL)    /* error: maloc() */
        return NULL;
    
    n->item = item;
    n->next = NULL;

    return n;
}


single_linked_list *init_single_linked_list(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    single_linked_list *list = NULL;
    if ((list = (single_linked_list *)malloc(sizeof(single_linked_list))) == NULL)   /* error: malloc() */
        return NULL;

    list->count = 0;
    list->head = list->tail = NULL;

    list->free_item = free_item;
    list->compare = compare;

    return list;
}

void destroy_single_linked_list(single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return ;

    single_linked_list_clear(list);
    free(list);
}


int single_linked_list_empty(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    return list->count == 0;
}

int single_linked_list_size(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    return list->count;
}


void *single_linked_list_front(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (single_linked_list_empty(list))
        return NULL;

    return list->head->item;
}

void *single_linked_list_back(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (single_linked_list_empty(list))
        return NULL;

    return list->tail->item;
}

void *single_linked_list_at(const single_linked_list *list, const int idx)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (idx < 0 || idx >= single_linked_list_size(list))   /* error: list out of ange */
        return NULL;

    struct node *curr = list->head;
    for (int i = 0; i < idx; i++)
        curr = curr->next;

    return curr->item;
}


/* search */
void *single_linked_list_find_item(const single_linked_list *list, const void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    int (*compare)(const void *, const void *) = list->compare;
    if (compare == NULL)    /* 비교 함수가 없으면 원하는 값을 찾을 수 없다. */
        return NULL;

    struct node *curr = list->head;
    while (curr && compare(curr->item, item) != 0)
        curr = curr->next;

    if (curr == NULL)    /* not found */
        return NULL;

    return curr->item;  /* found */
}

int single_linked_list_find_index(const single_linked_list *list, const void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    int (*compare)(const void *, const void *) = list->compare;
    if (compare == NULL)    /* 비교 함수가 없으면 원하는 값을 찾을 수 없다. */
        return -1;

    int index = 0;
    struct node *curr = list->head;
    while (curr && compare(curr->item, item) != 0)
    {
        curr = curr->next;   
        index++;
    }

    if (curr == NULL)    /* not found */
        return -1;

    return index;  /* found */
}


int single_linked_list_reverse(single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    if (list->count > 1)
    {
        struct node *prev_node = NULL;
        struct node *curr_node = list->head;
        list->tail = list->head;    /* 리스트를 뒤집으면 tail이 head가 됨 */
        while (curr_node)
        {
            struct node *temp = prev_node;
            prev_node = curr_node;
            curr_node = curr_node->next;
            prev_node->next = temp;
        }
        list->head = prev_node;     /* 리스트를 뒤집으면 head가 tail이 됨 */
    }

    return 0;
}

/* insert */
int single_linked_list_insert_front(single_linked_list *list, void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;

    struct node *new_node = init_node(item);

    new_node->next = list->head;
    if (single_linked_list_empty(list))
        list->tail = new_node;

    list->head = new_node;

    list->count++;

    return 0;
}

int single_linked_list_insert_back(single_linked_list *list, void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;

    struct node *new_node = init_node(item);

    if (single_linked_list_empty(list))
        list->head = new_node;
    else
        list->tail->next = new_node;

    list->tail = new_node;

    list->count++;

    return 0;
}

int single_linked_list_insert_at(single_linked_list *list, const int idx, void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    if (idx < 0 || idx >= single_linked_list_size(list))    /* error: out of range */
        return -1;
    
    if (item == NULL)    /* error: invalid arg */
        return -1;

    struct node *prev_node = NULL;
    struct node *curr_node = list->head;
    for (int i = 0; i < idx; i++)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    
    if (prev_node == NULL && curr_node == list->head)
    {
        return single_linked_list_insert_front(list, item);
    }
    else if (prev_node == list->tail && curr_node == NULL)
    {
        return single_linked_list_insert_back(list, item);
    }
    else
    {
        struct node *new_node = init_node(item);

        new_node->next = curr_node;
        prev_node->next = new_node;

        list->count++;
    }

    return 0;
}


/* delete */
void *single_linked_list_delete_front(single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (single_linked_list_empty(list))
        return NULL;

    struct node *curr_node = list->head;

    if (curr_node == list->tail)
        list->tail = NULL;

    list->head = list->head->next;
    
    void *ret_item = NULL;

    void (*free_item)(void *) = list->free_item;
    if (free_item)
        free_item(curr_node->item);
    else
        ret_item = curr_node->item;
    free(curr_node);
    list->count--;

    return ret_item;
}

void *single_linked_list_delete_back(single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (single_linked_list_empty(list))
        return NULL;

    struct node *curr_node = list->head;
    struct node *prev_node = NULL;
    while (curr_node->next)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (prev_node == NULL)
        list->head = NULL;
    else
        prev_node->next = NULL;

    list->tail = prev_node;
    
    void *ret_item = NULL;

    void (*free_item)(void *) = list->free_item;
    if (free_item)
        free_item(curr_node->item);
    else
        ret_item = curr_node->item;
    free(curr_node);
    list->count--;

    return ret_item;
}

void *single_linked_list_delete_at(single_linked_list *list, const int idx)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (idx < 0 || idx >= single_linked_list_size(list)) /* error: list out of ange */
        return NULL;

    struct node *curr_node = list->head;
    struct node *prev_node = NULL;
    for (int i = 0; i < idx; i++)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (prev_node == NULL && curr_node == list->head)
    {
        return single_linked_list_delete_front(list);
    }
    else if (prev_node == list->tail && curr_node == NULL)
    {
        return single_linked_list_delete_back(list);
    }
    else
    {
        prev_node->next = curr_node->next;

        void *ret_item = NULL;

        void (*free_item)(void *) = list->free_item;
        if (free_item)
            free_item(curr_node->item);
        else
            ret_item = curr_node->item;
        free(curr_node);
        list->count--;

        return ret_item;
    }

    return NULL;
}

void *single_linked_list_delete(single_linked_list *list, const void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    int (*compare)(const void *, const void *) = list->compare;
    if (compare == NULL)    /* 비교 함수가 없으면 원하는 값을 찾을 수 없다. */
        return NULL;

    struct node *prev_node = NULL;
    struct node *curr_node = list->head;
    while (curr_node && compare(curr_node->item, item) != 0)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (curr_node == NULL)    /* not found */
        return NULL;

    if (curr_node == list->head)
    {
        return single_linked_list_delete_front(list);
    }
    else if (curr_node == list->tail)
    {
        return single_linked_list_delete_back(list);
    }
    else
    {
        prev_node->next = curr_node->next;
        
        void *ret_item = NULL;

        void (*free_item)(void *) = list->free_item;
        if (free_item)
            free_item(curr_node->item);
        else
            ret_item = curr_node->item;
        free(curr_node);
        list->count--;

        return ret_item;
    }

    return NULL;
}


void single_linked_list_clear(single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return ;
        
    while (!single_linked_list_empty(list))
        single_linked_list_delete_front(list);
}


/* iterator */
iterator single_linked_list_begin(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (single_linked_list_empty(list))
        return NULL;

    return list->head;
}

iterator single_linked_list_next(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->next;
}

iterator single_linked_list_end(const single_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (single_linked_list_empty(list))
        return NULL;

    return NULL;
}

void *single_linked_list_iter_get(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->item;
}
