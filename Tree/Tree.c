#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Tree.h"
tree tree_init()
{
    return NULL;
}
tree tree_build(tree lsub, tree rsub, tree_item data)
{
    tree t;
    t = (struct tree_node*)malloc(sizeof(struct tree_node));
    if (!t) return NULL;
    t->info = data;
    t->left = lsub;
    t->right = rsub;
    return t;
}
tree tree_lsub(tree t)
{
    return t->left;
}
tree tree_rsub(tree t)
{
    return t->right;
}
void tree_delete(tree* t)
{
    if (!tree_empty(*t))
    {
        tree_delete(&((*t)->left));
        tree_delete(&((*t)->right));
        free(*t);
        *t = NULL;
    }
}
void tree_change_lsub(tree* t, tree new_tree)
{
    tree_delete(&((*t)->left));
    (*t)->left = new_tree;
}
void tree_change_rsub(tree* t, tree new_tree)
{
    tree_delete(&((*t)->right));
    (*t)->right = new_tree;
}
tree_item tree_root_retrieve(tree t)
{
    return t->info;
}
void tree_root_modify(tree* t, tree_item data)
{
    (*t)->info = data;
}
int tree_empty(tree t)
{
    return (t == NULL);
}
void pre_order(tree t)
{
    if (!tree_empty(t))//
    {
        printf("%d ", tree_root_retrieve(t));
        pre_order(t->left);
        pre_order(t->right);
    }
}
void in_order(tree t)
{
    if (!tree_empty(t))
    {
        in_order(t->left);
        printf("%d ", tree_root_retrieve(t));
        in_order(t->right);
    }
}
void post_order(tree t)
{
    if (!tree_empty(t))
    {
        post_order(t->left);
        post_order(t->right);
        printf("%d ", tree_root_retrieve(t));
    }
}

tree find(tree t, tree_item x) {
    if (tree_empty(t))
        return NULL;
    else {
        tree_item y = tree_root_retrieve(t);
        if (x == y) {
            return t;
        }
        if (x < y) {
            return find(t->left, x);
        }
        else {
            return find(t->right, x);
        }
    }
}

tree find_last_tree(tree t, tree_item x) {
    if (tree_empty(t)) {
        return NULL;
    }
    if (tree_empty(t->left) && tree_empty(t->right)) {
        return t;
    }

    tree_item y = tree_root_retrieve(t);
    if (x == y) {
        return t;
    }

    if (x < y) {
        if (tree_empty(t->left)) {
            return t;
        }
        return find_last_tree(t->left, x);
    } else {
        if (tree_empty(t->right)) {
            return t;
        }
        return find_last_tree(t->right, x);
    }
}
tree insert(tree t, tree_item x) {
    if (find(t,x)) {
        printf("Element %d exists in tree\n", x);
        return t;
    }
    else {
        tree v = find_last_tree(t,x);
        if (v != NULL) {
            tree_item y = v->info;
            tree w = tree_build(NULL, NULL, x);
            if (x < y) {
                v->left = w;
            }
            else {
                v->right = w;
            }
            return t;
        }
        else {
            v = tree_build(NULL, NULL, x);
            return v;
        }
    }
}
