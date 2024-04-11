#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct avl_tree
{
    int count;

    struct node *root;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
} avl_tree;
typedef struct node *iterator;

avl_tree *init_avl_tree(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_avl_tree(avl_tree *avl_tree);

int avl_tree_empty(const avl_tree *avl_tree);
int avl_tree_size(const avl_tree *avl_tree);

/* traversal */
void avl_tree_preorder(const avl_tree *avl_tree, void (*working)(void *));
void avl_tree_inorder(const avl_tree *avl_tree, void (*working)(void *));
void avl_tree_postorder(const avl_tree *avl_tree, void (*working)(void *));

int avl_tree_height(const avl_tree *avl_tree, const void *item);
void avl_tree_clear(avl_tree *avl_tree);

void *avl_tree_min(const avl_tree *avl_tree);
void *avl_tree_max(const avl_tree *avl_tree);

int avl_tree_insert(avl_tree *avl_tree, void *item);
int avl_tree_delete(avl_tree *avl_tree, void *item);
void *avl_tree_find(const avl_tree *avl_tree, const void *item);

/* iterator */
iterator avl_tree_begin(const avl_tree *avl_tree);
iterator avl_tree_next(const iterator iter);
iterator avl_tree_end(const avl_tree *avl_tree);
void *avl_tree_iter_get(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _AVL_TREE_H_ */