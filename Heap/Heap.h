#ifndef HEAP_H
#define HEAP_H

// Structure representing a max-heap
typedef struct {
    int* keys;   // Array of heap elements
    int count;   // Current number of elements
    int N;       // Maximum heap capacity
} Heap;


// Initializes a heap with a given maximum capacity
int H_init(Heap *H, int N);

// Returns the maximum element in the heap without removing it
int find_max(Heap* H);

// Restores heap property by moving the element at index i upward
int sift_up(Heap* H, int i);

// Restores heap property by moving the element at index i downward
int sift_down(Heap* H, int i);

// Inserts a new element into the heap
int H_insert(Heap *H, int x);

// Removes and returns the maximum element from the heap
int del_max(Heap *H);

// Builds a heap from an existing array of values
int Build_Heap(Heap *H, int* values);

#endif