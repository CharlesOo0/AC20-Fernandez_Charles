#ifndef _LISTE_H_
#define _LISTE_H_

/* Definition d'une liste chainée */

typedef struct _liste_chainee { // Ok pour le nom défini avant le contenu de la structure
    int data;
    struct _liste_chainee * next;
} liste_chainee_t; // Ici, on va retirer le _ qui précède et ajouter _t à la fin


// On doit exporter les fonctions avec leur déclaration (la signature) dans le .h
// Ces fonctions seront ensuite utilisables depuis le main avec la directive #include "liste.h"

/* LISTE CHAINEES SIMPLE */

void erase_list(liste_chainee_t* head);
void display_list(liste_chainee_t* head);
liste_chainee_t *add_head_list(liste_chainee_t* head, int data);
liste_chainee_t *add_tail_list(liste_chainee_t* head, int data);
int list_length(liste_chainee_t* head);
liste_chainee_t *add_target_list(liste_chainee_t* head, int data, int pos);
liste_chainee_t *delete_head_list(liste_chainee_t* head);
liste_chainee_t *delete_tail_list(liste_chainee_t* head);
liste_chainee_t *delete_target_list(liste_chainee_t* head, int pos);

/* LISTE DOUBLEMENT CHAINEES */


// Une liste chaînée est construite élément par élément, elle ne peut donc pas être créée à l'avance.
// On retire donc cette fonction des listes
//liste_chainee_t* create_list(int data);

#endif
