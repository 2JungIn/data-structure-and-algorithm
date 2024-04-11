#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct binary_tree 
{
    int count;

    struct node *root;

    void (*free_item)(void *);
    int (*compare)(const void *, const void *);
} binary_tree;
typedef struct node *iterator;

binary_tree *init_binary_tree(void (*free_item)(void *), int (*compare)(const void *, const void *));
void destroy_binary_tree(binary_tree *bin_tree);

int binary_tree_empty(const binary_tree *bin_tree);
int binary_tree_size(const binary_tree *bin_tree);

/* traversal */
void binary_tree_preorder(const binary_tree *bin_tree, void (*working)(void *));
void binary_tree_inorder(const binary_tree *bin_tree, void (*working)(void *));
void binary_tree_postorder(const binary_tree *bin_tree, void (*working)(void *));

int binary_tree_height(const binary_tree *bin_tree, const void *item);
void binary_tree_clear(binary_tree *bin_tree);

void *binary_tree_min(const binary_tree *bin_tree);
void *binary_tree_max(const binary_tree *bin_tree);

int binary_tree_insert(binary_tree *bin_tree, void *item);
int binary_tree_delete(binary_tree *bin_tree, void *item);
void *binary_tree_find(binary_tree *bin_tree, const void *item);

/* iterator */
iterator binary_tree_begin(const binary_tree *bin_tree);
iterator binary_tree_next(const iterator iter);
iterator binary_tree_end(const binary_tree *bin_tree);
void *binary_tree_iter_get(const iterator iter);

#ifdef __cplusplus
}
#endif

#endif  /* _BINARY_TREE_H_ */