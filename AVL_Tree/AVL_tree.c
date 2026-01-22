#include "AVL_tree.h"
#include <stdio.h>
#include <stdlib.h>


AVLTree *createNode(int data) {
    AVLTree *node = (AVLTree *)malloc(sizeof(AVLTree));
    if (!node) exit(1);
    node->data   = data;
    node->height = 0;
    node->left   = NULL;
    node->right  = NULL;
    return node;
}

void destroyTree(AVLTree *root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}


int getHeight(AVLTree *tree) {
    return tree ? tree->height : -1;
}

void updateHeight(AVLTree *tree) {
    int hl = getHeight(tree->left);
    int hr = getHeight(tree->right);
    tree->height = (hl > hr ? hl : hr) + 1;
}

int getBalance(AVLTree *tree) {
    if (!tree) return 0;
    // convention: balance = height(right) - height(left)
    return getHeight(tree->right) - getHeight(tree->left);
}



static void swapNodeData(AVLTree *a, AVLTree *b) {
    int t = a->data;
    a->data = b->data;
    b->data = t;
}

void rightRotate(AVLTree *tree) {
    if (!tree || !tree->left) return;

    swapNodeData(tree, tree->left);

    // rewire children like a classic RR rotation, but in-place
    AVLTree *oldRight = tree->right;        // save
    tree->right       = tree->left;         // move child up to right
    tree->left        = tree->right->left;  // left becomes left-left
    tree->right->left = tree->right->right; // child's left becomes child's right
    tree->right->right = oldRight;          // child's right becomes old right

    // fix heights (child first, then current)
    updateHeight(tree->right);
    updateHeight(tree);
}

void leftRotate(AVLTree *tree) {
    if (!tree || !tree->right) return;

    swapNodeData(tree, tree->right);

    AVLTree *oldLeft   = tree->left;
    tree->left         = tree->right;
    tree->right        = tree->left->right;
    tree->left->right  = tree->left->left;
    tree->left->left   = oldLeft;

    updateHeight(tree->left);
    updateHeight(tree);
}


void balance(AVLTree *tree) {
    if (!tree) return;
    int b = getBalance(tree);

    if (b == -2) { // too heavy on left: rotate right
        if (getBalance(tree->left) == 1) { // LR case → left then right
            leftRotate(tree->left);
        }
        rightRotate(tree);
    } else if (b == 2) { // too heavy on right: rotate left
        if (getBalance(tree->right) == -1) { // RL case → right then left
            rightRotate(tree->right);
        }
        leftRotate(tree);
    }
}


AVLTree* getMax(AVLTree* root) {
    if (!root) return NULL;
    while (root->right) root = root->right;
    return root;
}

AVLTree* getMin(AVLTree* root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}



AVLTree* insertNode(AVLTree* root, int data) {
    if (!root) return createNode(data);

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }

    updateHeight(root);
    balance(root);
    return root;
}

AVLTree* deleteNode(AVLTree* root, int data) {
    if (!root) return NULL;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // found
        if (!root->left || !root->right) {
            AVLTree *child = root->left ? root->left : root->right;
            free(root);
            return child;
        } else {
            AVLTree *pred = getMax(root->left);
            root->data = pred->data;
            root->left = deleteNode(root->left, pred->data);
        }
    }

    updateHeight(root);
    balance(root);
    return root;
}

AVLTree* search(AVLTree* root, int data) {
    if (!root) return NULL;
    if (root->data == data) return root;
    return (data < root->data) ? search(root->left, data)
                               : search(root->right, data);
}


void printTree(AVLTree* root) {
    if (!root) return;
    printTree(root->left);
    printf("%d ", root->data);
    printTree(root->right);
}
