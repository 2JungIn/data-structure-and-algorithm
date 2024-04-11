#include "../include/red-black-tree.h"
#include <stdlib.h>

typedef enum color
{
    COLOR_RED,
    COLOR_BLACK
} color;

struct node
{
    void *item;
    color color;

    struct node *parent;
    struct node *left;
    struct node *right;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
};


static struct node *init_node(void *item, void (*free_item)(void *), int (*compare)(const void *, const void *));
static void destroy_node(struct node *n);

static int max(const int a, const int b);
static int node_height(const struct node *n);

static int is_red(const struct node *n);
static int is_black(const struct node *n);

static void node_rotate_left(struct red_black_tree *rb_tree, struct node *x);
static void node_rotate_right(struct red_black_tree *rb_tree, struct node *x);

static void node_clear(struct node *n);

static void node_preorder(const struct node *n, void (*working)(void *));
static void node_inorder(const struct node *n, void (*working)(void *));
static void node_postorder(const struct node *n, void (*working)(void *));

static struct node *node_find(struct node *n, const void *item);

static struct node *node_min_item(struct node *n);
static struct node *node_max_item(struct node *n);


static void rb_insert_fixup(red_black_tree *rb_tree, struct node *z);
static int rb_insert(red_black_tree *rb_tree, struct node *z);
static void rb_transplant(red_black_tree *rb_tree, struct node *u, struct node *v);
static void rb_delete_fixup(red_black_tree *rb_tree, struct node *z);
static int rb_delete(red_black_tree *rb_tree, struct node *z);


static struct node *init_node(void *item, void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    struct node *n = NULL;
    if ((n = (struct node *)malloc(sizeof(struct node))) == NULL)   /* error: malloc() */
        return NULL;

    n->item = item;
    n->color = COLOR_RED;
    n->parent = n->left = n->right = NULL;

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



static int is_red(const struct node *n)
{
    if (n == NULL)  /* NIL노드는 검은색이다. */
        return 0;
    
    return n->color == COLOR_RED;
}

static int is_black(const struct node *n)
{
    return !is_red(n);
}


red_black_tree *init_red_black_tree(void (*free_item)(void *), int (*compare)(const void *, const void *))
{
    if (compare == NULL)    /* error: invalied arg */
        return NULL;

    red_black_tree *rb_tree = NULL;
    if ((rb_tree = (red_black_tree *)malloc(sizeof(red_black_tree))) == NULL) /* error: malloc() */
        return NULL;

    rb_tree->count = 0;

    rb_tree->root = NULL;

    rb_tree->free_item = free_item;
    rb_tree->compare = compare;

    return rb_tree;
}

void destroy_red_black_tree(red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalied arg */
        return ;

    red_black_tree_clear(rb_tree);
    free(rb_tree);
}


int red_black_tree_empty(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return -1;

    return rb_tree->count == 0;
}

int red_black_tree_size(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return -1;

    return rb_tree->count;
}


/* traversal */
static void node_preorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;
    
    if (working) 
        working(n->item);

    node_preorder(n->left, working);
    node_preorder(n->right, working);
}

void red_black_tree_preorder(const red_black_tree *rb_tree, void (*working)(void *))
{
    if (rb_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_preorder(rb_tree->root, working);
}


static void node_inorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;
    
    node_inorder(n->left, working);

    if (working) 
        working(n->item);

    node_inorder(n->right, working);
}

void red_black_tree_inorder(const red_black_tree *rb_tree, void (*working)(void *))
{
    if (rb_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_inorder(rb_tree->root, working);
}


static void node_postorder(const struct node *n, void (*working)(void *))
{
    if (n == NULL)
        return ;

    node_postorder(n->left, working);
    node_postorder(n->right, working);

    if (working) 
        working(n->item);
}

void red_black_tree_postorder(const red_black_tree *rb_tree, void (*working)(void *))
{
    if (rb_tree == NULL)    /* error: invalied arg */
        return ;
    
    node_postorder(rb_tree->root, working);
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

int red_black_tree_height(const red_black_tree *rb_tree, const void *item)
{
    if (rb_tree == NULL)    /* error: invalied arg */
        return 0;

    if (item == NULL)    /* error: invalied arg */
        return 0;

    return node_height(node_find(rb_tree->root, item));
}


static void node_clear(struct node *n)
{
    if (n == NULL)
        return ;

    node_clear(n->left);
    node_clear(n->right);
    destroy_node(n);
}

void red_black_tree_clear(red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return ;

    node_clear(rb_tree->root);

    rb_tree->root = NULL;
    rb_tree->count = 0;
}


static struct node *node_min_item(struct node *n)
{
    if (n == NULL)   /* error: invalid arg */
        return NULL;
    
    return n->left == NULL ? n : node_min_item(n->left);
}

void *red_black_tree_min(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *min_node = node_min_item(rb_tree->root);
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

void *red_black_tree_max(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return NULL;
    
    struct node *max_node = node_max_item(rb_tree->root);
    if (max_node == NULL)
        return NULL;

    return max_node->item;
}


static void node_rotate_left(red_black_tree *rb_tree, struct node *x)
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
    **/
    struct node *y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;
    
    y->parent = x->parent;
    if (x->parent == NULL)
        rb_tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

static void node_rotate_right(red_black_tree *rb_tree, struct node *x)
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
    **/
    struct node *y = x->left;
    x->left = y->right;

    if (y->right)
        y->right->parent = x;
    
    y->parent = x->parent;
    if (x->parent == NULL)
        rb_tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->right = x;
    x->parent = y;
}


static void rb_insert_fixup(red_black_tree *rb_tree, struct node *z)
{
    while (is_red(z->parent))
    {
        if (z->parent == z->parent->parent->left)
        {
            struct node *y = z->parent->parent->right;
            if (is_red(y))
            {
                z->parent->color = COLOR_BLACK;
                y->color = COLOR_BLACK;
                z->parent->parent->color = COLOR_RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->right)
            {
                z = z->parent;
                node_rotate_left(rb_tree, z);
            }
            else
            {
                z->parent->color = COLOR_BLACK;
                z->parent->parent->color = COLOR_RED;
                node_rotate_right(rb_tree, z->parent->parent);
            }
        }
        else
        {
            struct node *y = z->parent->parent->left;
            if (is_red(y))
            {
                z->parent->color = COLOR_BLACK;
                y->color = COLOR_BLACK;
                z->parent->parent->color = COLOR_RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->left)
            {
                z = z->parent;
                node_rotate_right(rb_tree, z);
            }
            else
            {
                z->parent->color = COLOR_BLACK;
                z->parent->parent->color = COLOR_RED;
                node_rotate_left(rb_tree, z->parent->parent);
            }
        }
    }

    rb_tree->root->color = COLOR_BLACK;
}

static int rb_insert(red_black_tree *rb_tree, struct node *z)
{
    int (*compare)(const void *, const void *) = z->compare;
    
    struct node *y = NULL;
    struct node *x = rb_tree->root;
    while (x)
    {
        y = x;
        if (compare(z->item, x->item) < 0)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        rb_tree->root = z;
    else if (compare(z->item, y->item) < 0)
        y->left = z;
    else
        y->right = z;

    rb_insert_fixup(rb_tree, z);
    rb_tree->count++;

    return 0;
}

int red_black_tree_insert(red_black_tree *rb_tree, void *item)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    return rb_insert(rb_tree, init_node(item, rb_tree->free_item, rb_tree->compare));
}


static void rb_transplant(red_black_tree *rb_tree, struct node *u, struct node *v)
{
    if (u->parent == NULL)
        rb_tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    
    if (v)
        v->parent = u->parent;
}

static void rb_delete_fixup(red_black_tree *rb_tree, struct node *z)
{
    if (z == NULL)
        return ;

    while (z != rb_tree->root && is_black(z))
    {
        if (z == z->parent->left)
        {
            struct node *w = z->parent->right;
            if (is_red(w))
            {
                w->color = COLOR_BLACK;
                z->parent->color = COLOR_RED;
                node_rotate_left(rb_tree, z->parent);
                w = z->parent->right;
            }
            if (is_black(w->left) && is_black(w->right))
            {
                w->color = COLOR_RED;
                z = z->parent;
            }
            else if (is_black(w->right))
            {
                w->left->color = COLOR_BLACK;
                w->color = COLOR_RED;
                node_rotate_right(rb_tree, w);
                w = z->parent->right;
            }
            else
            {
                w->color = z->parent->color;
                z->parent->color = COLOR_BLACK;
                w->right->color = COLOR_BLACK;
                node_rotate_left(rb_tree, z->parent);
                z = rb_tree->root;
            }
        }
        else
        {
            struct node *w = z->parent->left;
            if (is_red(w))
            {
                w->color = COLOR_BLACK;
                z->parent->color = COLOR_RED;
                node_rotate_right(rb_tree, z->parent);
                w = z->parent->left;
            }
            if (is_black(w->left) && is_black(w->right))
            {
                w->color = COLOR_RED;
                z = z->parent;
            }
            else if (is_black(w->right))
            {
                w->right->color = COLOR_BLACK;
                w->color = COLOR_RED;
                node_rotate_left(rb_tree, w);
                w = z->parent->left;
            }
            else
            {
                w->color = z->parent->color;
                z->parent->color = COLOR_BLACK;
                w->left->color = COLOR_BLACK;
                node_rotate_right(rb_tree, z->parent);
                z = rb_tree->root;
            }
        }
    }

    z->color = COLOR_BLACK;
}

static int rb_delete(red_black_tree *rb_tree, struct node *z)
{    
    if (z == NULL)
        return -1;

    struct node *x = NULL;
    struct node *y = z;
    int y_original_color = y->color;

    if (z->left == NULL)
    {
        x = z->right;
        rb_transplant(rb_tree, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        rb_transplant(rb_tree, z, z->left);
    }
    else
    {
        y = node_min_item(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rb_transplant(rb_tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rb_transplant(rb_tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    rb_tree->count--;
    destroy_node(z);

    if (y_original_color == COLOR_BLACK)
        rb_delete_fixup(rb_tree, x);
    
    return 0;
}

int red_black_tree_delete(red_black_tree *rb_tree, void *item)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return -1;

    if (item == NULL)    /* error: invalid arg */
        return -1;
    
    return rb_delete(rb_tree, node_find(rb_tree->root, item));
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

void *red_black_tree_find(const red_black_tree *rb_tree, const void *item)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (item == NULL)   /* error: invalid arg */
        return NULL;
    
    struct node *result = node_find(rb_tree->root, item);

    if (result == NULL)  /* not found */
        return NULL;

    return result->item;
}


/* iterator */
iterator red_black_tree_begin(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (red_black_tree_empty(rb_tree))
        return NULL;

    return node_min_item(rb_tree->root);
}

iterator red_black_tree_next(const iterator iter)
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

iterator red_black_tree_end(const red_black_tree *rb_tree)
{
    if (rb_tree == NULL)    /* error: invalid arg */
        return NULL;

    if (red_black_tree_empty(rb_tree))
        return NULL;

    return NULL;
}

void *red_black_tree_iter_get(const iterator iter)
{
    if (iter == NULL)
        return NULL;
    
    return iter->item;
}
