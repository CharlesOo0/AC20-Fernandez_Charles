#ifndef _GRAPHE_H_
#define _GRAPHE_H_

    /* Définition d'un graphe */

/* La liste des noeuds liées */

typedef struct _node {
    int data;
    int weight;
    struct _node *next;
}node_t;

/* La liste des noeuds */

typedef struct _adjencyList {
    int data;
    struct _node *begin;
}adjencyList_t;

/* Le graphe */

typedef struct _graph {
    bool is_oriented;
    int memory_allocated;
    int tab_memory;
    adjencyList_t *tab;
}graph_t;

/* Djikstra Node */

typedef struct _node_djikstra {
    int data;
    bool seen;
    int *path;
    int weight;
}node_d_t;

/* Prototypes */

graph_t *create_graph(int vertices, bool is_oriented);
void erase_graph(graph_t* g);
bool is_empty(graph_t *g);
int contain(graph_t *g, int target);
graph_t *add_vertex(graph_t *g, int vertex);
graph_t *remove_vertex(graph_t *g, int target);
graph_t *add_edge(graph_t* g, int src, int dst, int weight);
graph_t *remove_edge(graph_t* g, int src, int dst);
void display_graphe(graph_t *g);
adjencyList_t *increase_memory(graph_t* g);
adjencyList_t *reduce_memory(graph_t* g);

#endif
