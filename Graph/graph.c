#include "graph.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdjNode {
    int v;
    struct AdjNode* next;
} AdjNode;

struct Graph {
    int n;
    int directed;
    AdjNode** adj;
};


static int valid_vertex(const Graph* g, int v) {
    return g && v >= 0 && v < g->n;
}

static int list_contains(AdjNode* head, int v) {
    for (AdjNode* p = head; p; p = p->next) {
        if (p->v == v) return 1;
    }
    return 0;
}

static int list_add_unique(AdjNode** head, int v) {
    if (list_contains(*head, v)) return 1; // already exists
    AdjNode* node = (AdjNode*)malloc(sizeof(*node));
    if (!node) return 0;
    node->v = v;
    node->next = *head;
    *head = node;
    return 1;
}

static int list_remove_one(AdjNode** head, int v) {
    AdjNode* prev = NULL;
    AdjNode* cur = *head;
    while (cur) {
        if (cur->v == v) {
            if (prev) prev->next = cur->next;
            else *head = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

static void list_free(AdjNode* head) {
    while (head) {
        AdjNode* next = head->next;
        free(head);
        head = next;
    }
}

// queue for BFS
typedef struct {
    int* a;
    int head, tail, cap;
} IntQueue;

static int q_init(IntQueue* q, int cap) {
    q->a = (int*)malloc(sizeof(int) * (size_t)cap);
    if (!q->a) return 0;
    q->head = 0;
    q->tail = 0;
    q->cap = cap;
    return 1;
}
static void q_free(IntQueue* q) { free(q->a); q->a = NULL; }
static int q_empty(const IntQueue* q) { return q->head == q->tail; }
static int q_push(IntQueue* q, int x) {
    if (q->tail >= q->cap) return 0;
    q->a[q->tail++] = x;
    return 1;
}
static int q_pop(IntQueue* q, int* out) {
    if (q_empty(q)) return 0;
    *out = q->a[q->head++];
    return 1;
}

// stack for DFS
typedef struct {
    int* a;
    int top;
    int cap;
} IntStack;

static int s_init(IntStack* s, int cap) {
    s->a = (int*)malloc(sizeof(int) * (size_t)cap);
    if (!s->a) return 0;
    s->top = 0;
    s->cap = cap;
    return 1;
}
static void s_free(IntStack* s) { free(s->a); s->a = NULL; }
static int s_empty(const IntStack* s) { return s->top == 0; }
static int s_push(IntStack* s, int x) {
    if (s->top >= s->cap) return 0;
    s->a[s->top++] = x;
    return 1;
}
static int s_pop(IntStack* s, int* out) {
    if (s_empty(s)) return 0;
    *out = s->a[--s->top];
    return 1;
}



Graph* graph_create(int n, int directed) {
    if (n <= 0) return NULL;

    Graph* g = (Graph*)calloc(1, sizeof(*g));
    if (!g) return NULL;

    g->n = n;
    g->directed = directed ? 1 : 0;

    g->adj = (AdjNode**)calloc((size_t)n, sizeof(AdjNode*));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    return g;
}

void graph_destroy(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        list_free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

int graph_vertex_count(const Graph* g) {
    return g ? g->n : 0;
}

int graph_is_directed(const Graph* g) {
    return g ? g->directed : 0;
}

int graph_add_edge(Graph* g, int u, int v) {
    if (!valid_vertex(g, u) || !valid_vertex(g, v)) return 0;

    if (!list_add_unique(&g->adj[u], v)) return 0;
    if (!g->directed) {
        if (!list_add_unique(&g->adj[v], u)) return 0;
    }
    return 1;
}

int graph_remove_edge(Graph* g, int u, int v) {
    if (!valid_vertex(g, u) || !valid_vertex(g, v)) return 0;

    int removed = list_remove_one(&g->adj[u], v);
    if (!g->directed) {
        removed = list_remove_one(&g->adj[v], u) || removed;
    }
    return removed ? 1 : 0;
}

int graph_has_edge(const Graph* g, int u, int v) {
    if (!valid_vertex(g, u) || !valid_vertex(g, v)) return 0;
    return list_contains(g->adj[u], v);
}

int graph_bfs(const Graph* g, int start, void (*visit)(int v, void* user), void* user) {
    if (!valid_vertex(g, start)) return 0;

    int* visited = (int*)calloc((size_t)g->n, sizeof(int));
    if (!visited) return 0;

    IntQueue q;
    if (!q_init(&q, g->n)) {
        free(visited);
        return 0;
    }

    visited[start] = 1;
    q_push(&q, start);

    int cur;
    while (q_pop(&q, &cur)) {
        if (visit) visit(cur, user);

        for (AdjNode* p = g->adj[cur]; p; p = p->next) {
            int nxt = p->v;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                q_push(&q, nxt);
            }
        }
    }

    q_free(&q);
    free(visited);
    return 1;
}

int graph_dfs(const Graph* g, int start, void (*visit)(int v, void* user), void* user) {
    if (!valid_vertex(g, start)) return 0;

    int* visited = (int*)calloc((size_t)g->n, sizeof(int));
    if (!visited) return 0;

    IntStack st;
    if (!s_init(&st, g->n)) {
        free(visited);
        return 0;
    }

    s_push(&st, start);

    int cur;
    while (s_pop(&st, &cur)) {
        if (visited[cur]) continue;
        visited[cur] = 1;

        if (visit) visit(cur, user);

        for (AdjNode* p = g->adj[cur]; p; p = p->next) {
            if (!visited[p->v]) {
                s_push(&st, p->v);
            }
        }
    }

    s_free(&st);
    free(visited);
    return 1;
}

int graph_shortest_path_bfs(const Graph* g, int start, int target, int* out_path, int out_cap) {
    if (!valid_vertex(g, start) || !valid_vertex(g, target) || !out_path || out_cap <= 0) return -1;

    int* visited = (int*)calloc((size_t)g->n, sizeof(int));
    int* parent  = (int*)malloc(sizeof(int) * (size_t)g->n);
    if (!visited || !parent) {
        free(visited);
        free(parent);
        return -1;
    }
    for (int i = 0; i < g->n; i++) parent[i] = -1;

    IntQueue q;
    if (!q_init(&q, g->n)) {
        free(visited);
        free(parent);
        return -1;
    }

    visited[start] = 1;
    q_push(&q, start);

    int cur;
    while (q_pop(&q, &cur)) {
        if (cur == target) break;

        for (AdjNode* p = g->adj[cur]; p; p = p->next) {
            int nxt = p->v;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                parent[nxt] = cur;
                q_push(&q, nxt);
            }
        }
    }

    q_free(&q);

    if (!visited[target]) {
        free(visited);
        free(parent);
        return 0;
    }

    int len = 0;
    for (int v = target; v != -1; v = parent[v]) {
        len++;
    }
    if (len > out_cap) {
        free(visited);
        free(parent);
        return -1;
    }

    int idx = len - 1;
    for (int v = target; v != -1; v = parent[v]) {
        out_path[idx--] = v;
    }

    free(visited);
    free(parent);
    return len;
}