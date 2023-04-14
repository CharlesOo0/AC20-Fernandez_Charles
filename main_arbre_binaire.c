#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "arbre.c"

int main() {

    arbre_t *un_arbre = NULL;

    // Crée un arbre manuellement
    un_arbre = create_tree(1);
        add_tree(un_arbre,1,2,0);
            add_tree(un_arbre,2,4,0);
            add_tree(un_arbre,2,5,1);
        add_tree(un_arbre,1,3,1);
            add_tree(un_arbre,3,6,0);
            add_tree(un_arbre,3,7,1);
    
    display_tree_postorder(un_arbre);
    printf("\n");

    printf("Le parent de 2 est %d\n",get_parent(un_arbre,6,0));

    if (is_node(un_arbre,15)) {
        printf("Noeud présent\n");
    }else {
        printf("Noeud absent\n");
    }

    //erase_tree(un_arbre);
    un_arbre = NULL;
    

    int nodes[7] = {1,5,7,2,8,4,1};
    // Représentation d'un arbre par étage en quelque sorte
    // On écrit l'étage 1 de gauche à droite
    // Puis l'étage 2 toujours de gauche à droite etc
    //               1
    //              / \ 
    //             5   7
    //            / \ / \ 
    //           2  8 4  1

    un_arbre = tree_maker(nodes, sizeof(nodes)/sizeof(int));
    erase_node(un_arbre, 8);

    //Test la racine en tant que cible
    //erase_node(un_arbre,1);
    //un_arbre = NULL;

    display_tree_postorder(un_arbre);

    printf("number of nodes : %d",node_counting(un_arbre));

    return EXIT_SUCCESS;
}
