#include <stdio.h>
#include <stdlib.h>
#include "graphe.c"

int main() {

    graph_t *g = create_graph(5,true);

    display_graphe(g);

    erase_graph(g);

    g = NULL;

    g = create_graph(3,true);

    g = add_vertex(g, 47801);

    g = remove_vertex(g,2);

    display_graphe(g);

    //printf("\n dqsdqs %d",g->tab[3].data); // Problème à résoudre le réalloc n'enlève pas le noeud du tableau

    g = add_edge(g,1,3,15);
    g = add_edge(g,3,1,15);
    g = add_edge(g,1,47801,45);

    g = remove_edge(g,3,1);

    display_graphe(g);

    return EXIT_SUCCESS;
}
