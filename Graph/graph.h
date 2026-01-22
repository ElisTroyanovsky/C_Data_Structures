#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h> // size_t

// Opaque structure representing a graph
typedef struct Graph Graph;

// Creates a graph with n vertices (0..n-1), directed or undirected
Graph* graph_create(int n, int directed);

// Frees all memory associated with the graph
void graph_destroy(Graph* g);

// Returns the number of vertices in the graph
int graph_vertex_count(const Graph* g);

// Returns 1 if the graph is directed, 0 otherwise
int graph_is_directed(const Graph* g);

// Adds an edge from u to v (and v to u if undirected)
int graph_add_edge(Graph* g, int u, int v);

// Removes the edge from u to v (and v to u if undirected)
int graph_remove_edge(Graph* g, int u, int v);

// Checks whether an edge from u to v exists
int graph_has_edge(const Graph* g, int u, int v);

// Performs a breadth-first search starting from the given vertex
int graph_bfs(const Graph* g, int start, void (*visit)(int v, void* user), void* user);

// Performs a depth-first search (iterative) starting from the given vertex
int graph_dfs(const Graph* g, int start, void (*visit)(int v, void* user), void* user);

// Finds the shortest path between two vertices in an unweighted graph using BFS
int graph_shortest_path_bfs(const Graph* g, int start, int target, int* out_path, int out_cap);

#endif