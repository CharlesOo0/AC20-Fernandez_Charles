#ifndef _LISTE_V2_H_
#define _LISTE_V2_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Définition liste chainée simple */
typedef struct _liste_chainee  {

    int data;
    struct _liste_chainee *next;

}liste_chainee_t;

/* Défintion fiche propriété d'une liste chainée */
typedef struct _liste_propriete {

    struct _liste_chainee *head;
    struct _liste_chainee *tail;
    int list_length;

}liste_propriete_t;

/* Initialisation des prototypes */

void erase_list_v2(liste_propriete_t* propriete);
void display_list_v2(liste_propriete_t *propriete);
void display_property(liste_propriete_t* propriete);
liste_chainee_t *add_head_list_v2(liste_propriete_t* propriete, int data);
liste_chainee_t *add_tail_list_v2(liste_propriete_t* propriete, int data);
liste_chainee_t *delete_head_list_v2(liste_propriete_t* propriete);


#endif
