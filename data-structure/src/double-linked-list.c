#include "../include/double-linked-list.h"
#include <stdlib.h>

struct node
{
    void *item;
    struct node *prev;
    struct node *next;
};

static struct node *init_node(void *item)
{
    struct node *n = NULL;
    if ((n = (struct node *)malloc(sizeof(struct node))) == NULL)    /* error: maloc() */
        return NULL;
    
    n->item = item;
    n->prev = n->next = NULL;

    return n;
}


double_linked_list *init_double_linked_list(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    double_linked_list *list = NULL;
    if ((list = (double_linked_list *)malloc(sizeof(double_linked_list))) == NULL)   /* error: malloc() */
        return NULL;

    list->count = 0;
    list->head = list->tail = NULL;

    list->free_item = free_item;
    list->compare = compare;

    return list;
}

void destroy_double_linked_list(double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return ;

    double_linked_list_clear(list);
    free(list);
}


int double_linked_list_empty(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    return list->count == 0;
}

int double_linked_list_size(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    return list->count;
}


void *double_linked_list_front(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (double_linked_list_empty(list))
        return NULL;

    return list->head->item;
}

void *double_linked_list_back(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (double_linked_list_empty(list))
        return NULL;

    return list->tail->item;
}

void *double_linked_list_at(const double_linked_list *list, const int idx)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (idx < 0 || idx >= double_linked_list_size(list))   /* error: list out of range */
        return NULL;

    struct node *curr = list->head;
    for (int i = 0; i < idx; i++)
        curr = curr->next;

    return curr->item;
}


void *double_linked_list_find_item(const double_linked_list *list, const void *item)
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

int double_linked_list_find_index(const double_linked_list *list, const void *item)
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


int double_linked_list_reverse(double_linked_list *list)
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
            prev_node = curr_node;
            curr_node = curr_node->next;

            struct node *temp = prev_node->prev;
            prev_node->prev = prev_node->next;
            prev_node->next = temp;
        }
        list->head = prev_node;     /* 리스트를 뒤집으면 head가 tail이 됨 */
    }

    return 0;
}


int double_linked_list_insert_front(double_linked_list *list, void *item)
{
    if (list == NULL)   /* error: invalid arg */
        return -1;

    if (item == NULL)   /* error: invalid arg */
        return -1;

    struct node *new_node = init_node(item);

    new_node->next = list->head;
    if (double_linked_list_empty(list))
        list->tail = new_node;
    else
        list->head->prev = new_node;

    list->head = new_node;

    list->count++;

    return 0;
}

int double_linked_list_insert_back(double_linked_list *list, void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;
    
    if (item == NULL)    /* error: invalid arg */
        return -1;

    struct node *new_node = init_node(item);

    new_node->prev = list->tail;
    new_node->next = NULL;
    if (double_linked_list_empty(list))
        list->head = new_node;
    else
        list->tail->next = new_node;

    list->tail = new_node;

    list->count++;

    return 0;
}

int double_linked_list_insert_at(double_linked_list *list, const int idx, void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return -1;

    if (idx < 0 || idx >= double_linked_list_size(list))    /* error: out of range */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;

    struct node *curr_node = list->head;
    for (int i = 0; i < idx; i++)
        curr_node = curr_node->next;
    
    if (curr_node == list->head)
    {
        return double_linked_list_insert_front(list, item);
    }
    else if (curr_node == list->tail)
    {
        return double_linked_list_insert_back(list, item);
    }
    else
    {
        struct node *new_node = init_node(item);

        new_node->next = curr_node;
        new_node->prev = curr_node->prev;
        curr_node->prev->next = new_node;
        curr_node->prev = new_node;

        list->count++;
    }

    return 0;
}


void *double_linked_list_delete_front(double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (double_linked_list_empty(list))
        return NULL;

    struct node *curr_node = list->head;

    if (list->head == list->tail)
    {
        list->head = list->tail = NULL;
    }
    else
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    
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

void *double_linked_list_delete_back(double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (double_linked_list_empty(list))
        return NULL;

    struct node *curr_node = list->tail;
    if (list->head == list->tail)
    {
        list->head = list->tail = NULL;
    }
    else
    {
        list->tail = curr_node->prev;
        list->tail->next = NULL;
    }
    
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

void *double_linked_list_delete_at(double_linked_list *list, const int idx)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;
    
    if (idx < 0 || idx >= double_linked_list_size(list)) /* error: list out of ange */
        return NULL;

    struct node *curr_node = list->head;
    for (int i = 0; i < idx; i++)
        curr_node = curr_node->next;

    if (curr_node == list->head)
    {
        return double_linked_list_delete_front(list);
    }
    else if (curr_node == list->tail)
    {
        return double_linked_list_delete_back(list);
    }
    else
    {
        curr_node->next->prev = curr_node->prev;
        curr_node->prev->next = curr_node->next;

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

void *double_linked_list_delete(double_linked_list *list, const void *item)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    int (*compare)(const void *, const void *) = list->compare;
    if (compare == NULL)    /* 비교 함수가 없으면 원하는 값을 찾을 수 없다. */
        return NULL;

    struct node *curr_node = list->head;
    while (curr_node && compare(curr_node->item, item) != 0)
        curr_node = curr_node->next;

    if (curr_node == NULL)    /* not found */
        return NULL;

    if (curr_node == list->head)
    {
        return double_linked_list_delete_front(list);
    }
    else if (curr_node == list->tail)
    {
        return double_linked_list_delete_back(list);
    }
    else
    {
        curr_node->next->prev = curr_node->prev;
        curr_node->prev->next = curr_node->next;

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


void double_linked_list_clear(double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return ;
        
    while (!double_linked_list_empty(list))
        double_linked_list_delete_front(list);
}


iterator double_linked_list_begin(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (double_linked_list_empty(list))
        return NULL;

    return list->head;
}

iterator double_linked_list_next(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->next;
}

iterator double_linked_list_end(const double_linked_list *list)
{
    if (list == NULL)    /* error: invalid arg */
        return NULL;

    if (double_linked_list_empty(list))
        return NULL;

    return NULL;
}

void *double_linked_list_iter_get(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->item;
}
