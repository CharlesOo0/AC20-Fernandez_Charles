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

/* noeud de Djikstra */

typedef struct _node_djikstra {
    int data;
    bool painted;
    int nametag;
    int  *path;
    int path_length;
    struct _node *begin;
}node_d_t;

/* Prototypes */

// Création / Suppression
graph_t *create_graph(int vertices, bool is_oriented);
void erase_graph(graph_t* g);

// Modification
graph_t *add_vertex(graph_t *g, int vertex);
graph_t *remove_vertex(graph_t *g, int target);
graph_t *add_edge(graph_t* g, int src, int dst, int weight);
graph_t *remove_edge(graph_t* g, int src, int dst);

// Gestionnaire mémoire
adjencyList_t *increase_memory(graph_t* g);
adjencyList_t *reduce_memory(graph_t* g);

// Propriété
bool is_empty(graph_t *g);
int contain(graph_t *g, int target);

// Affichage
void display_graphe(graph_t *g);

/* Algorithme */

int getIndex(node_d_t *tab, int target, int length);
bool isPainted(node_d_t *tab, int length);
int searchCurrent(node_d_t *tab, int length);
void concatene_path(node_d_t *tab, int indexCurrent, int indexTarget);
bool out_nodes_painted(node_d_t *tab, int indexTarget, int length);

void Djikstra(graph_t *g, int start);
void parcour_largeur(graph_t *g, int start);
void parcour_profondeur(graph_t *g, int start);


#endif
