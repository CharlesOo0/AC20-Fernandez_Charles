#include <stdlib.h>
#include <stdio.h>

void main()
{
    _liste_chainee * Charles = (_liste_chainee*)malloc(sizeof(_liste_chainee*));

    //display_list(Charles); Problème Affiche les valeur des cases mémoire ???

    Charles = create_list(4);

    display_list(Charles);

    add_head_list(&Charles, 2);
    add_head_list(&Charles, 7);
    add_head_list(&Charles, 1);
    add_head_list(&Charles, 9);

    display_list(Charles);

    erase_list(Charles);

    return;
}
