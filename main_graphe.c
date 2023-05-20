#include <stdio.h>
#include <stdlib.h>
#include "graphe.c"

int main() {

    /*
    graph_t *g = create_graph(5,true);

    display_graphe(g);

    erase_graph(g);

    g = NULL;

    g = create_graph(3,true);

    for (int i = 4; i < 22; ++i) {
        g = add_vertex(g, i);
    }
    printf("\n%d %d",g->memory_allocated,g->tab_memory);  
    printf("\n %d ",g->tab[0].data);

    for (int j = 0; j < 23; ++j) {
        g = remove_vertex(g, j);
    }

    g = add_edge(g,2,1,15);
    g = add_edge(g,3,1,15);
    g = add_edge(g,4,1,15);

    g = remove_vertex(g,1);

    display_graphe(g);

    g = add_edge(g,4,5,15);
    g = add_edge(g,4,6,15);
    g = add_edge(g,5,6,15);
    g = add_edge(g,5,14,15);
    g = add_edge(g,5,13,15);

    g = remove_vertex(g,14);

    display_graphe(g);

    //printf("\ndzqhdzhq %d",5/10);*/

    graph_t *g = create_graph(5,true);
    g = add_edge(g,1,3,18);
    g = add_edge(g,1,5,3);
    g = add_edge(g,2,3,4);
    g = add_edge(g,2,1,8);
    g = add_edge(g,4,2,1);
    g = add_edge(g,5,2,10);
    g = add_edge(g,5,4,2);

    //display_graphe(g);

    Djikstra(g,1);


    return EXIT_SUCCESS;
}
