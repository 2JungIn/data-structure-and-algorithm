#include "../include/avl-tree.h"
#include <stdlib.h>

struct node
{
    void *item;
    int height;

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
static int node_balance(const struct node *n);
static void node_height_update(struct node *n);
static struct node *node_rebalancing(struct node *n);
static struct node *node_rotate_left(struct node *parent_node);
static struct node *node_rotate_right(struct node *parent_node);

static void node_clear(struct node *n);

static void node_preorder(const struct node *n, void (*working)(void *));
static void node_inorder(const struct node *n, void (*working)(void *));
static void node_postorder(const struct node *n, void (*working)(void *));

static struct node *node_insert(avl_tree *avl_tree, struct node *n, void *item, struct node *parent);
static struct node *node_delete(avl_tree *avl_tree, struct node *n, void *item);
static struct node *node_find(struct node *n, const void *item);

static struct node *node_min_item(struct node *n);
static struct node *node_max_item(struct node *n);


static struct node *init_node(void *item, struct node *parent, void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    struct node *n = NULL;
    if ((n = (struct node *)malloc(sizeof(struct node))) == NULL)   /* error: malloc() */
        return NULL;

    n->item = item;
    n->height = 1;

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


avl_tree *init_avl_tree(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    if (compare == NULL)    /* error: invalied arg */
        return NULL;

    avl_tree *new_avl_tree = NULL;
    if ((new_avl_tree = (avl_tree *)malloc(sizeof(avl_tree))) == NULL) /* error: malloc() */
        return NULL;

    new_avl_tree->count = 0;

    new_avl_tree->root = NULL;

    new_avl_tree->free_item = free_item;
    new_avl_tree->compare = compare;

    return new_avl_tree;
}

void destroy_avl_tree(avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalied arg */
        return ;

    avl_tree_clear(avl_tree);
    free(avl_tree);
}


int avl_tree_empty(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)
        return -1;

    return avl_tree->count == 0;
}

int avl_tree_size(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)
        return -1;

    return avl_tree->count;
}


/* traversal */
static void node_preorder(const struct node *n, void (*working)(void *))
{
    if (n != NULL)
    {
        if (working != NULL) 
            working(n->item);

        node_preorder(n->left, working);
        node_preorder(n->right, working);
    }
}

void avl_tree_preorder(const avl_tree *avl_tree, void (*working)(void *))
{
    if (avl_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_preorder(avl_tree->root, working);
}


static void node_inorder(const struct node *n, void (*working)(void *))
{
    if (n != NULL)
    {
        node_inorder(n->left, working);

        if (working != NULL) 
            working(n->item);

        node_inorder(n->right, working);
    }
}

void avl_tree_inorder(const avl_tree *avl_tree, void (*working)(void *))
{
    if (avl_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_inorder(avl_tree->root, working);
}


static void node_postorder(const struct node *n, void (*working)(void *))
{
    if (n != NULL)
    {
        node_postorder(n->left, working);
        node_postorder(n->right, working);

        if (working != NULL) 
            working(n->item);
    }
}

void avl_tree_postorder(const avl_tree *avl_tree, void (*working)(void *))
{
    if (avl_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_postorder(avl_tree->root, working);
}


static int max(const int a, const int b)
{
    return (a > b ? a : b);
}

static int node_height(const struct node *n)
{
    if (n == NULL)
        return 0;
    
    return n->height;
}

int avl_tree_height(const avl_tree *avl_tree, const void *item)
{
    if (avl_tree == NULL)   /* error: invalied arg */
        return 0;

    if (item == NULL)    /* error: invalied arg */
        return 0;

    return node_height(node_find(avl_tree->root, item));
}


static int node_balance(const struct node *n)
{
    return node_height(n->left) - node_height(n->right);
}

static void node_height_update(struct node *n)
{    
    n->height = 1 + max(node_height(n->left), node_height(n->right));
}

static struct node *node_rotate_left(struct node *parent_node)
{
    /**
     *       rotate left
     * 
     *   1                  2
     *  / \               /   \
     * ..  2      ->     1     3
     *    / \           / \   / \ 
     *   x   3         ..  x .. ..
     *      / \
     *     .. ..
    */
    struct node *right_child = parent_node->right;
    parent_node->right = right_child->left;
    right_child->left = parent_node;

    /* parent update */
    right_child->parent = parent_node->parent;
    parent_node->parent = right_child;

    node_height_update(parent_node);
    node_height_update(right_child);

    return right_child;
}

static struct node *node_rotate_right(struct node *parent_node)
{
    /**
     *          rotate right
     * 
     *       3               2
     *      / \            /   \
     *     2  ..   ->     1     3
     *    / \            / \   / \ 
     *   1   x          .. .. x   ..
     *  / \
     * .. ..
    */
    struct node *left_child = parent_node->left;
    parent_node->left = left_child->right;
    left_child->right = parent_node;

    /* parent update */
    left_child->parent = parent_node->parent;
    parent_node->parent = left_child;

    node_height_update(parent_node);
    node_height_update(left_child);

    return left_child;
}

static struct node *node_rebalancing(struct node *n)
{
    node_height_update(n);

    if (node_balance(n) > 1 && node_balance(n->left) >= 0)
    {
        /**
         *          rotate right
         * 
         *       3               2
         *      / \            /   \
         *     2  ..   ->     1     3
         *    / \            / \   / \ 
         *   1   x          .. .. x   ..
         *  / \
         * .. ..
        */  
        return node_rotate_right(n);
    }
    else if (node_balance(n) < -1 && node_balance(n->right) <= 0)
    {
        /**
         *       rotate left
         * 
         *   1                  2
         *  / \               /   \
         * ..  2      ->     1     3
         *    / \           / \   / \ 
         *   x   3         ..  x .. ..
         *      / \
         *     .. ..
        */
        return node_rotate_left(n);
    }
    else if (node_balance(n) > 1 && node_balance(n->left) < 0)
    {
        /**
         *           rotate left      rotate right
         * 
         *       3                 3               2 
         *      / \               / \             / \
         *     1  ..    ->       2  ..   ->      1   3
         *    / \               / \             / \ / \
         *  ..   2             1  ..          .. .. .. ..
         *      / \           / \
         *    ..   ..        .. ..
        */
        n->left = node_rotate_left(n->left);
        return node_rotate_right(n);
    }
    else if (node_balance(n) < -1 && node_balance(n->right) > 0)
    {
        /**
         *           rotate right        rotate left
         * 
         *       1                  1                   2 
         *      / \                / \                 / \
         *     ..  3     ->      ..   2       ->      1   3
         *        / \                / \             / \ / \
         *       2  ..              ..  3          .. .. .. ..
         *      / \                    / \
         *     .. ..                  .. ..
        */
        n->right = node_rotate_right(n->right);
        return node_rotate_left(n);
    }

    return n;
}


static void node_clear(struct node *n)
{
    if (n == NULL)
        return ;
        
    node_clear(n->left);
    node_clear(n->right);
    destroy_node(n);
}

void avl_tree_clear(avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return ;

    node_clear(avl_tree->root);

    avl_tree->root = NULL;
    avl_tree->count = 0;
}


static struct node *node_min_item(struct node *n)
{
    if (n == NULL)   /* error: invalid arg */
        return NULL;
    
    return n->left == NULL ? n : node_min_item(n->left);
}

void *avl_tree_min(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *min_node = node_min_item(avl_tree->root);
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

void *avl_tree_max(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *max_node = node_max_item(avl_tree->root);
    if (max_node == NULL)
        return NULL;

    return max_node->item;
}


static struct node *node_insert(avl_tree *avl_tree, struct node *n, void *item, struct node *parent)
{
    if (n == NULL)
    {
        avl_tree->count++;
        return init_node(item, parent, avl_tree->free_item, avl_tree->compare);
    }

    int ret_compare = n->compare(n->item, item);

    if (ret_compare > 0)
    {
        n->left = node_insert(avl_tree, n->left, item, n);
    }
    else if (ret_compare < 0)
    {
        n->right = node_insert(avl_tree, n->right, item, n);
    }
    else
    {
        void (*free_item)(void *) = n->free_item;
        if (free_item)
            free_item(n->item);

        n->item = item;
    }

    return node_rebalancing(n);
}

int avl_tree_insert(avl_tree *avl_tree, void *item)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    avl_tree->root = node_insert(avl_tree, avl_tree->root, item, NULL);

    return 0;
}


static struct node *node_delete(avl_tree *avl_tree, struct node *n, void *item)
{
    if (n == NULL)
        return NULL;
    
    int ret_compare = n->compare(n->item, item);

    if (ret_compare > 0)
    {
        n->left = node_delete(avl_tree, n->left, item);
    }
    else if (ret_compare < 0)
    {
        n->right = node_delete(avl_tree, n->right, item);
    }
    else
    {
        if (n->left == NULL)
        {
            struct node *temp = n->right;
            if (temp)
                temp->parent = n->parent;
            destroy_node(n);
            avl_tree->count--;

            return temp;
        }
        else if (n->right == NULL)
        {
            struct node *temp = n->left;
            if (temp)
                temp->parent = n->parent;
            destroy_node(n);
            avl_tree->count--;

            return temp;
        }
        else 
        {
            struct node *temp = node_min_item(n->right);
            
            /* swap */
            void *temp_item = n->item;
            n->item = temp->item;
            temp->item = temp_item;

            n->right = node_delete(avl_tree, n->right, temp->item);
        }
    }

    return node_rebalancing(n);
}

int avl_tree_delete(avl_tree *avl_tree, void *item)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    avl_tree->root = node_delete(avl_tree, avl_tree->root, item);

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

void *avl_tree_find(const avl_tree *avl_tree, const void *item)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (item == NULL)   /* error: invalid arg */
        return NULL;
    
    struct node *result = node_find(avl_tree->root, item);

    if (result == NULL)  /* not found */
        return NULL;

    return result->item;
}


/* iterator */
iterator avl_tree_begin(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (avl_tree_empty(avl_tree))
        return NULL;

    return node_min_item(avl_tree->root);
}

iterator avl_tree_next(const iterator iter)
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

iterator avl_tree_end(const avl_tree *avl_tree)
{
    if (avl_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (avl_tree_empty(avl_tree))
        return NULL;

    return NULL;
}

void *avl_tree_iter_get(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->item;
}
