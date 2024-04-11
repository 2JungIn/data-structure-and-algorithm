#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct red_black_tree
{
    int count;

    struct node *root;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
} red_black_tree;
typedef struct node *iterator;

red_black_tree *init_red_black_tree(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_red_black_tree(red_black_tree *rb_tree);

int red_black_tree_empty(const red_black_tree *rb_tree);
int red_black_tree_size(const red_black_tree *rb_tree);

/* traversal */
void red_black_tree_preorder(const red_black_tree *rb_tree, void (*working)(void *));
void red_black_tree_inorder(const red_black_tree *rb_tree, void (*working)(void *));
void red_black_tree_postorder(const red_black_tree *rb_tree, void (*working)(void *));

int red_black_tree_height(const red_black_tree *rb_tree, const void *item);
void red_black_tree_clear(red_black_tree *rb_tree);

void *red_black_tree_min(const red_black_tree *rb_tree);
void *red_black_tree_max(const red_black_tree *rb_tree);

int red_black_tree_insert(red_black_tree *rb_tree, void *item);
int red_black_tree_delete(red_black_tree *rb_tree, void *item);
void *red_black_tree_find(const red_black_tree *rb_tree, const void *item);

/* iterator */
iterator red_black_tree_begin(const red_black_tree *rb_tree);
iterator red_black_tree_next(const iterator iter);
iterator red_black_tree_end(const red_black_tree *rb_tree);
void *red_black_tree_iter_get(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _RED_BLACK_TREE_H_ */