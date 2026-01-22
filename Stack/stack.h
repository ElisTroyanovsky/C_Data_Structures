#ifndef STACK_H
#define STACK_H

// Type stored in the stack
typedef int stack_item;

// Node of a linked-list based stack
typedef struct stack_node {
    stack_item info;
    struct stack_node *next;
} stack_node;

typedef struct {
    stack_node *top;
} stack;


// Initializes an empty stack
void stack_init(stack *s);

// Returns 1 if the stack is empty, 0 otherwise
int stack_empty(stack s);

// Always returns 0 for a linked-list based stack (no capacity limit)
int stack_full(stack s);

// Pushes a new element onto the stack
void stack_push(stack *s, stack_item x);

// Removes and returns the top element of the stack
stack_item stack_pop(stack *s);

// Prints all elements of the stack
void printstack(stack *s);

// Reverses the stack using an auxiliary stack
stack turn(stack *s, stack s1);

#endif