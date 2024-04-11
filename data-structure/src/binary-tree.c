#include "../include/binary-tree.h"
#include <stdlib.h>

struct node
{
    void *item;

    struct node *parent;
    struct node *left;
    struct node *right;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
};

static struct node *init_node(void *item, struct node *parent, void (*free_item)(void *), int (*compare)(const void *, const void *));
static void destroy_node(struct node *n);

static int max(const int a, const int b);
static int node_height(const struct node *n);

static void node_clear(struct node *n);

static void node_preorder(const struct node *n, void (*working)(void *));
static void node_inorder(const struct node *n, void (*working)(void *));
static void node_postorder(const struct node *n, void (*working)(void *));

static struct node *node_insert(binary_tree *bin_tree, struct node *n, void *item, struct node *parent);
static struct node *node_delete(binary_tree *bin_tree, struct node *n, void *item);
static struct node *node_find(struct node *n, const void *item);

static struct node *node_min_item(struct node *n);
static struct node *node_max_item(struct node *n);


static struct node *init_node(void *item, struct node *parent, void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    struct node *n = NULL;
    if ((n = (struct node *)malloc(sizeof(struct node))) == NULL)   /* error: malloc() */
        return NULL;

    n->item = item;
    n->parent = parent;
    n->left = n->right = NULL;

    n->free_item = free_item;
    n->compare = compare;

    return n;
}

static void destroy_node(struct node *n)
{
    if (n == NULL)
        return ;

    void (*free_item)(void *) = n->free_item;
    if (free_item)
        free_item(n->item);

    free(n);
}


binary_tree *init_binary_tree(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    if (compare == NULL)    /* error: invalid arg */
        return NULL;

    binary_tree *new_bin_tree = NULL;
    if ((new_bin_tree = (binary_tree *)malloc(sizeof(binary_tree))) == NULL) /* error: malloc() */
        return NULL;

    new_bin_tree->count = 0;

    new_bin_tree->root = NULL;

    new_bin_tree->free_item = free_item;
    new_bin_tree->compare = compare;

    return new_bin_tree;
}

void destroy_binary_tree(binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return ;

    binary_tree_clear(bin_tree);
    free(bin_tree);
}


int binary_tree_empty(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return -1;

    return bin_tree->compare == 0;
}

int binary_tree_size(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return -1;

    return bin_tree->count;
}


/* traversal */
static void node_preorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;

    if (working != NULL) 
        working(n->item);

    node_preorder(n->left, working);
    node_preorder(n->right, working);
}

void binary_tree_preorder(const binary_tree *bin_tree, void (*working)(void *))
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return ;
    
    node_preorder(bin_tree->root, working);
}


static void node_inorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;

    node_inorder(n->left, working);

    if (working != NULL) 
        working(n->item);

    node_inorder(n->right, working);
}

void binary_tree_inorder(const binary_tree *bin_tree, void (*working)(void *))
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return ;
    
    node_inorder(bin_tree->root, working);
}


static void node_postorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;
    
    node_postorder(n->left, working);
    node_postorder(n->right, working);

    if (working != NULL) 
        working(n->item);
}

void binary_tree_postorder(const binary_tree *bin_tree, void (*working)(void *))
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return ;
    
    node_postorder(bin_tree->root, working);
}



static int max(const int a, const int b)
{
    return (a > b ? a : b);
}

static int node_height(const struct node *n)
{
    if (n == NULL)
        return 0;
    
    return 1 + max(node_height(n->left), node_height(n->right));
}

int binary_tree_height(const binary_tree *bin_tree, const void *item)
{
    if (bin_tree == NULL)   /* error: invalid arg */
        return 0;
        
    if (item == NULL)    /* error: invalid arg */
        return 0;

    struct node *result = node_find(bin_tree->root, item);

    if (result == NULL)  /* not found */
        return 0;

    return node_height(result);
}


static void node_clear(struct node *n)
{
    if (n == NULL)
        return ;
        
    node_clear(n->left);
    node_clear(n->right);
    destroy_node(n);
}

void binary_tree_clear(binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return ;

    node_clear(bin_tree->root);

    bin_tree->root = NULL;
    bin_tree->count = 0;
}


static struct node *node_min_item(struct node *n)
{
    if (n == NULL)   /* error: invalid arg */
        return NULL;
    
    return n->left == NULL ? n : node_min_item(n->left);
}

void *binary_tree_min(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *min_node = node_min_item(bin_tree->root);
    if (min_node == NULL)
        return NULL;

    return min_node->item;
}


static struct node *node_max_item(struct node *n)
{
    if (n == NULL)   /* error: invalid arg */
        return NULL;
    
    return n->right == NULL ? n : node_max_item(n->right);
}

void *binary_tree_max(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *max_node = node_max_item(bin_tree->root);
    if (max_node == NULL)
        return NULL;

    return max_node->item;
}


static struct node *node_insert(binary_tree *bin_tree, struct node *n, void *item, struct node *parent)
{
    if (n == NULL)
    {
        bin_tree->count++;
        return init_node(item, parent, bin_tree->free_item, bin_tree->compare);
    }

    int ret_compare = n->compare(n->item, item);

    if (ret_compare > 0)
    {
        n->left = node_insert(bin_tree, n->left, item, n);
    }
    else if (ret_compare < 0)
    {
        n->right = node_insert(bin_tree, n->right, item, n);
    }
    else
    {
        void (*free_item)(void *) = n->free_item;
        if (free_item)
            free_item(n->item);

        n->item = item;
    }
    
    return n;
}

int binary_tree_insert(binary_tree *bin_tree, void *item)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    bin_tree->root = node_insert(bin_tree, bin_tree->root, item, NULL);
    
    return 0;
}


static struct node *node_delete(binary_tree *bin_tree, struct node *n, void *item)
{
    if (n == NULL)
        return NULL;
    
    int ret_compare = n->compare(n->item, item);

    if (ret_compare > 0)
    {
        n->left = node_delete(bin_tree, n->left, item);
    }
    else if (ret_compare < 0)
    {
        n->right = node_delete(bin_tree, n->right, item);
    }
    else
    {
        if (n->left == NULL)
        {
            struct node *temp = n->right;
            if (temp)
                temp->parent = n->parent;
            destroy_node(n);
            bin_tree->count--;

            return temp;
        }
        else if (n->right == NULL)
        {
            struct node *temp = n->left;
            if (temp)
                temp->parent = n->parent;
            destroy_node(n);
            bin_tree->count--;

            return temp;
        }
        else 
        {
            struct node *temp = node_min_item(n->right);
            
            /* swap */
            void *temp_item = n->item;
            n->item = temp->item;
            temp->item = temp_item;

            n->right = node_delete(bin_tree, n->right, temp->item);
        }
    }

    return n;
}

int binary_tree_delete(binary_tree *bin_tree, void *item)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    bin_tree->root = node_delete(bin_tree, bin_tree->root, item);

    return 0;
}


static struct node *node_find(struct node *n, const void *item)
{
    if (n == NULL)
        return NULL;

    int ret_compare = n->compare(n->item, item);

    if (ret_compare > 0)
        return node_find(n->left, item);
    else if (ret_compare < 0)
        return node_find(n->right, item);
    else
        return n;
    
    return NULL;
}

void *binary_tree_find(binary_tree *bin_tree, const void *item)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (item == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *result = node_find(bin_tree->root, item);

    if (result == NULL)  /* not found */
        return NULL;

    return result->item;
}


/* iterator */
iterator binary_tree_begin(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (binary_tree_empty(bin_tree))
        return NULL;

    return node_min_item(bin_tree->root);
}

iterator binary_tree_next(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    if (iter->right != NULL)
        return node_min_item(iter->right);
    
    iterator temp = iter;
    while (temp->parent && temp == temp->parent->right)
        temp = temp->parent;
        
    return temp->parent;
}

iterator binary_tree_end(const binary_tree *bin_tree)
{
    if (bin_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (binary_tree_empty(bin_tree))
        return NULL;

    return NULL;
}

void *binary_tree_iter_get(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->item;
}
