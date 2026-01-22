#ifndef TREE_H
#define TREE_H

// Type stored in the tree nodes
typedef int tree_item;

// Node of a binary tree
typedef struct tree_node {
    tree_item info;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

typedef tree_node* tree;


// Creates and returns an empty tree (NULL)
tree tree_init();

// Builds a new tree node with given data and left/right subtrees
tree tree_build(tree lsub, tree rsub, tree_item data);

// Returns the left subtree of the given tree
tree tree_lsub(tree t);

// Returns the right subtree of the given tree
tree tree_rsub(tree t);

// Replaces the left subtree of the given tree
void tree_change_lsub(tree* t, tree new_tree);

// Replaces the right subtree of the given tree
void tree_change_rsub(tree* t, tree new_tree);

// Returns the value stored in the root node
tree_item tree_root_retrieve(tree t);

// Updates the value stored in the root node
void tree_root_modify(tree* t, tree_item data);

// Returns 1 if the tree is empty (NULL), 0 otherwise
int tree_empty(tree t);

// Prints the tree using pre-order traversal
void pre_order(tree t);

// Prints the tree using in-order traversal
void in_order(tree t);

// Prints the tree using post-order traversal
void post_order(tree t);

// Searches for a node containing x and returns its pointer (or NULL)
tree find(tree t, tree_item x);

// Finds the last matching node containing x according to traversal logic
tree find_last_tree(tree t, tree_item x);

// Inserts x into the tree and returns the (possibly new) root
tree insert(tree t, tree_item x);

#endif