#ifndef AVL_TREE_H
#define AVL_TREE_H

// Node structure for an AVL self-balancing binary search tree
typedef struct AVLTree {
    int data;                  // Value stored in the node
    int height;                // Height of the node
    struct AVLTree *left;      // Pointer to left child
    struct AVLTree *right;     // Pointer to right child
} AVLTree;


// Creates a new AVL tree node with the given data
AVLTree *createNode(int data);

// Frees all nodes in the AVL tree
void destroyTree(AVLTree *root);


// Returns the height of the given node
int getHeight(AVLTree *tree);

// Updates the height of the given node based on its children
void updateHeight(AVLTree *tree);

// Computes the balance factor of the node (left height − right height)
int getBalance(AVLTree *tree);


// Performs a right rotation around the given node
void rightRotate(AVLTree *tree);

// Performs a left rotation around the given node
void leftRotate(AVLTree *tree);

// Rebalances the subtree rooted at the given node
void balance(AVLTree *tree);


// Returns the node with the maximum value in the subtree
AVLTree *getMax(AVLTree *root);

// Returns the node with the minimum value in the subtree
AVLTree *getMin(AVLTree *root);


// Inserts a value into the AVL tree and returns the new root
AVLTree *insertNode(AVLTree *root, int data);

// Deletes a value from the AVL tree and returns the new root
AVLTree *deleteNode(AVLTree *root, int data);

// Searches for a value in the AVL tree and returns its node if found
AVLTree *search(AVLTree *root, int data);


// Prints the AVL tree structure (in-order or visual representation)
void printTree(AVLTree *root);

#endif