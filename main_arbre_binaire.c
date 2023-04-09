#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "arbre.c"

int main() {

    arbre_t *un_arbre = NULL;

    // Crée un arbre manuellement
    un_arbre = create_tree(1);

    un_arbre->Agauche = create_tree(2);
        un_arbre->Agauche->Agauche = create_tree(3);
        un_arbre->Agauche->Adroite = create_tree(3);

    un_arbre->Adroite = create_tree(2);
        un_arbre->Adroite->Agauche = create_tree(3);
        un_arbre->Adroite->Adroite = create_tree(3);
    
    display_tree_postorder(un_arbre);
    printf("\n");

    erase_tree(un_arbre);
    un_arbre = NULL;
    

    int nodes[7] = {1,2,2,3,3,3,3};

    un_arbre = tree_maker(nodes, sizeof(nodes)/sizeof(int));

    display_tree_postorder(un_arbre);

    return EXIT_SUCCESS;
}
