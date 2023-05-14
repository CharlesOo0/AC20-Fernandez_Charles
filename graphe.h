#ifndef _GRAPHE_H_
#define _GRAPHE_H_

    /* Définition d'un booléen */

typedef enum{
    false,
    true
}Bool;

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
    Bool is_oriented;
    int nb_vertices;
    adjencyList_t *tab;
}graph_t;

/* Prototypes */

graph_t *create_graph(int vertices, Bool is_oriented);
void erase_graph(graph_t* g);
Bool is_empty(graph_t *g);
int contain(graph_t *g, int target);
graph_t *add_vertex(graph_t *g, int vertex);
graph_t *remove_vertex(graph_t *g, int target);
graph_t *add_edge(graph_t* g, int src, int dst, int weight);
graph_t *remove_edge(graph_t* g, int src, int dst);
void display_graphe(graph_t *g);

#endif
