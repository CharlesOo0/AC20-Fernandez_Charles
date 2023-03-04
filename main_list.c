#include <stdlib.h>
#include <stdio.h>

#include "liste.c" // On inclut l'entête de liste, avec des " " car le répertoire local n'est pas recherché pour les includes.
// #include <liste.h> nécessite l'ajout de -I. dans les options de la compilation.

//void main() { Attention, il est préférable de retourner un int pour permettre au système de connaître l'état d'exécution du programme.
int main() {
    // On va déclarer un pointeur sur une liste. Un pointeur est un entier sur le même nombre de bits
    // que l'architecture du PC (4 octets sur systèmes 32 bits, 8 octets sur systèmes 64 bits)
    // Le pointeur n'est pas alloué par un malloc. Seule la valeur du type pointé peut être obtenue
    // par malloc.
    // Dans le cas présent :
    // liste_chainee_t * Charles = (liste_chainee_t*)malloc(sizeof(liste_chainee_t*));i
    // aurait pour effet de faire pointer la variable Charles sur l'espace en mémoire nécessaire
    // à un pointeur (sizeof(liste_chainee_t *)), soit 8 octets, alors que la taille de la structure
    // liste_chainee_t est égale à 12 (4 pour int + 8 pour le pointeur next), ce qui est incorrect
    // Une affectation possible serait :
    // liste_chainee_t *une_liste = (liste_chainee_t *) malloc(sizeof(liste_chainee_t));
    // où on remarque l'absence de l'étoile dans le sizeof, indiquant bien qu'on demande la taille
    // d'un type liste_chainee_t.
    // Dans notre cas d'application, on n'allouera au début aucune mémoire et on initialisera le pointeur à NULL :
    liste_chainee_t *une_liste = NULL;

    //display_list(Charles); Problème Affiche les valeur des cases mémoire ??? -> voir la remarque ci-dessus concernant l'usage de la mémoire
    display_list(une_liste); // Ne devrait rien afficher

    // une_liste = create_list(4); Pas pour le fonctionnement d'une liste chaînée, on ne connaît pas sa taille a priori.

    // add_head_list(&une_liste, 2);
    une_liste = add_head_list(une_liste, 2);
    une_liste = add_head_list(une_liste, 7);
    une_liste = add_head_list(une_liste, 1);
    une_liste = add_head_list(une_liste, 9);

    display_list(une_liste);

    erase_list(une_liste);
    // Il faut remettre une_liste à NULL sinon une réutilisation ultérieure plante :
    une_liste = NULL;
    display_list(une_liste);

    for (int i=0; i<10; ++i)
        une_liste = add_tail_list(une_liste, i+1);
 
    une_liste = add_target_list(une_liste, 15, 5);
    display_list(une_liste);
    une_liste = add_target_list(une_liste, 152, 0);
    display_list(une_liste);
    une_liste = add_target_list(une_liste, 1500, 12);
    display_list(une_liste);
    une_liste = add_target_list(une_liste, 1500, 15);
    display_list(une_liste);

    une_liste = delete_head_list(une_liste);
    display_list(une_liste);
    
    une_liste = delete_tail_list(une_liste);
    display_list(une_liste);

    une_liste = delete_target_list(une_liste, 10);
    display_list(une_liste);

    return EXIT_SUCCESS;
}
