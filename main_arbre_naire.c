#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "arbre_naire.c"


int main() {

    narbre_t *un_arbre = create_ntree(1);
        un_arbre->child = create_ntree(2);
            un_arbre->child->child = create_ntree(5);
            un_arbre->child->child->sibling = create_ntree(6);
        un_arbre->child->sibling = create_ntree(3);
            un_arbre->child->sibling->child = create_ntree(7);
        un_arbre->child->sibling->sibling = create_ntree(4);
            un_arbre->child->sibling->sibling->child = create_ntree(8);
            un_arbre->child->sibling->sibling->child->sibling = create_ntree(9);
            un_arbre->child->sibling->sibling->child->sibling->sibling = create_ntree(10);

    // On à crée un arbre n-aire manuellement :
    //                  1
    //              /   |    \ 
    //             2    3     4
    //            /\    |   / | \ 
    //           5  6   7  8  9 10

    printf("Voici un arbre : \n");
    display_ntree(un_arbre,0);

    add_sibling(un_arbre,5,11);

    printf("Voici un arbre : \n");
    display_ntree(un_arbre,0);

    add_child(un_arbre,5,12);

    printf("Voici un arbre : \n");
    display_ntree(un_arbre,0);

    printf("Nombres de noeuds : %d",node_counting(un_arbre));

    if (is_node(un_arbre,10)) {
        printf("\nLa node est présente !");
    }

    printf("\nLe parent : %d\n",find_parent(un_arbre,12,NULL)->data);

    //delete_node(un_arbre,10);

    printf("Voici un arbre : \n");
    display_ntree(un_arbre,0);

    print_path(un_arbre,10);

    printf("\n%d",get_level(un_arbre,5,0));

    return EXIT_SUCCESS;
}
