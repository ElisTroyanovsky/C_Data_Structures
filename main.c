#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Stack/stack.h"
#include "Queue/queue.h"
#include "Heap/Heap.h"
#include "Tree/Tree.h"
#include "AVL_Tree/AVL_tree.h"
#include "HashTable/hashTable.h"
#include "Graph/graph.h"

static void print_section(const char* title) {
    printf("\n==================== %s ====================\n", title);
}

static void visit_print_vertex(int v, void* user) {
    (void)user;
    printf("%d ", v);
}

// Stack tests
static void test_stack(void) {
    print_section("STACK");

    stack s;
    stack_init(&s);

    assert(stack_empty(s) == 1);
    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);

    assert(stack_empty(s) == 0);

    int a = stack_pop(&s);
    int b = stack_pop(&s);
    int c = stack_pop(&s);

    printf("Popped: %d %d %d (expected 30 20 10)\n", a, b, c);
    assert(a == 30 && b == 20 && c == 10);
    assert(stack_empty(s) == 1);

    printf("STACK: OK\n");
}

// Queue tests
static void test_queue(void) {
    print_section("QUEUE");

    queue q;
    queue_init(&q);

    assert(queue_empty(q) == 1);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    assert(queue_empty(q) == 0);

    int a = dequeue(&q);
    int b = dequeue(&q);
    int c = dequeue(&q);

    printf("Dequeued: %d %d %d (expected 1 2 3)\n", a, b, c);
    assert(a == 1 && b == 2 && c == 3);
    assert(queue_empty(q) == 1);

    printf("QUEUE: OK\n");
}

// Heap tests (max-heap)
static void test_heap(void) {
    print_section("HEAP (MAX-HEAP)");

    Heap h = {0};
    (void)H_init(&h, 16);


    int values[] = {5, 20, 3, 15, 40, 1, 9};
    int n = sizeof(values)/sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        int ok = H_insert(&h, values[i]);
    }
    printf("Max = %d\n", find_max(&h));

    int mx = find_max(&h);
    printf("Max (peek): %d (expected 40)\n", mx);
    assert(mx == 40);

    int prev = del_max(&h);
    printf("del_max sequence: %d ", prev);

    for (int i = 1; i < n; i++) {
        int cur = del_max(&h);
        printf("%d ", cur);
        assert(prev >= cur);
        prev = cur;
    }
    printf("\n");

    free(h.keys);
    h.keys = NULL;

    printf("HEAP: OK\n");
}


// Binary Search Tree tests

static void test_tree(void) {
    print_section("TREE (BST)");

    tree t = tree_init();

    int values[] = {10, 5, 15, 12, 18, 3, 7};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    for (int i = 0; i < n; i++) {
        t = insert(t, values[i]);
    }
    printf("Root value: %d\n", tree_root_retrieve(t));

    printf("In-order traversal (should be sorted): ");
    in_order(t);
    printf("\n");

    assert(find(t, 12) != NULL);
    assert(find(t, 999) == NULL);

    printf("TREE: OK\n");
}


static void test_avl(void) {
    print_section("AVL TREE");

    AVLTree* root = NULL;
    int values[] = {10, 20, 30, 40, 50, 25};
    int n = (int)(sizeof(values) / sizeof(values[0]));

    for (int i = 0; i < n; i++) {
        root = insertNode(root, values[i]);
    }

    printf("AVL print:\n");
    printTree(root);

    assert(search(root, 25) != NULL);
    assert(search(root, 999) == NULL);

    root = deleteNode(root, 40);
    assert(search(root, 40) == NULL);

    destroyTree(root);
    root = NULL;

    printf("AVL: OK\n");
}

// HashTable tests
static void test_hashtable(void) {
    print_section("HASH TABLE");

    HashTable* ht = ht_create(8);
    assert(ht != NULL);

    assert(ht_put(ht, "coffee", 12) == 1);
    assert(ht_put(ht, "rent", 2000) == 1);
    assert(ht_put(ht, "coffee", 15) == 1);

    int v = 0;
    assert(ht_get(ht, "coffee", &v) == 1 && v == 15);
    assert(ht_get(ht, "rent", &v) == 1 && v == 2000);
    assert(ht_get(ht, "missing", &v) == 0);

    assert(ht_contains(ht, "rent") == 1);
    assert(ht_remove(ht, "rent") == 1);
    assert(ht_contains(ht, "rent") == 0);

    printf("Size: %zu, Capacity: %zu\n", ht_size(ht), ht_capacity(ht));

    ht_destroy(ht);
    ht = NULL;

    printf("HASH TABLE: OK\n");
}

// Graph tests (BFS, DFS, shortest path)


static void test_graph(void) {
    print_section("GRAPH");

    Graph* g = graph_create(6, 0);
    assert(g != NULL);

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 2);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 4, 5);

    printf("BFS from 0: ");
    assert(graph_bfs(g, 0, visit_print_vertex, NULL) == 1);
    printf("\n");

    printf("DFS from 0: ");
    assert(graph_dfs(g, 0, visit_print_vertex, NULL) == 1);
    printf("\n");

    int path[16];
    int len = graph_shortest_path_bfs(g, 0, 5, path, 16);
    assert(len > 0);

    printf("Shortest path 0 -> 5 (len=%d): ", len);
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    graph_destroy(g);
    g = NULL;

    printf("GRAPH: OK\n");
}

// Main
int main(void) {
    printf("Running Data Structures tests...\n");

    test_stack();
    test_queue();

    test_heap();
    test_tree();
    test_avl();
    test_hashtable();
    test_graph();

    printf("\n✅ ALL TESTS PASSED\n");
    return 0;
}