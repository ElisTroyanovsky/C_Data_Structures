#ifndef QUEUE_H
#define QUEUE_H

// Type stored in the queue
typedef int queue_item;

// Node of a linked-list based queue
typedef struct queue_node {
    queue_item info;
    struct queue_node *next;
} queue_node;

typedef struct {
    queue_node *head;
    queue_node *rear;
} queue;


// Initializes an empty queue
void queue_init(queue *q);

// Adds an element to the rear of the queue
void enqueue(queue *q, queue_item x);

// Removes and returns the front element of the queue
queue_item dequeue(queue *q);

// Returns the front element without removing it
queue_item queue_top(queue q);

// Returns 1 if the queue is empty, 0 otherwise
int queue_empty(queue q);

// Prints all elements of the queue
void queue_print(queue *q);

// Creates a copy of the source queue
void copy(queue *q, queue *cop);

#endif