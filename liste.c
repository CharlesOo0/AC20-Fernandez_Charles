#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

/* Création d'une liste chainées */

_liste_chainee* create_list(int data){

    _liste_chainee *new_node = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise la mémoire du nouvelle élément

    new_node->next = NULL; // Pas de node suivante
    new_node->data = data; // On ajoute la data au première élément

    return new_node;

}

/* Efface une liste chainées */

void erase_list(_liste_chainee* head){
    _liste_chainee *temp = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise d'un pointeur pour free chaque élément

    if( head == NULL ){
        return;
    }

    while( head != NULL ){
        temp = head;
        head = head->next;
        free(temp);
    }

    return;
}

/* Affiche une liste chainées */

void display_list(_liste_chainee* head){

    _liste_chainee *ptr = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise un pointeur sur la liste à afficher

    if( head == NULL ){ // Si la liste est vide alors elle n'est pas initialiser
        printf("La liste est vide");
        return;
    }

    ptr = head; // On initialise le pointeur en tête de liste
    int i = 1;

    printf("  Liste chainées : \n ("); 
    while( ptr != NULL ){ // On itère à travers la liste chainées jusqu'aux dernières élément non NULL

        printf(" %d ",ptr->data);
        ptr = ptr->next; // Passe d'un élément à un autre
        ++i;

    }
    printf(")\n\n");
    return;
}

/* Ajout d'un élément en tête de liste */

void add_head_list(_liste_chainee** head, int data){

    _liste_chainee *new_node = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise la mémoire du nouvelle élément

    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = *head; // La tête devient l'élément suivant du nouvelle élément
    *head = new_node;       // Le nouvelle élément devient la tête

    return;
}

/* Ajout d'un élément en fin de liste */

void add_tail_list(_liste_chainee** head, int data){
    _liste_chainee *new_node = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise la mémoire du nouvelle élément
    
    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = NULL;

    if( *head == NULL ){ // Si la liste est vide alors le nouvelle élément est la tête
        *head = new_node;
    }

    _liste_chainee *ptr = (_liste_chainee*)malloc(sizeof(_liste_chainee*)); // Initialise un pointeur sur la liste pour itérer dedans
    ptr = *head;
    while( ptr->next != NULL ){
        ptr = ptr->next;
    }

    ptr->next = new_node; // Remplace le dernière élément NULL par notre nouvelle élément

    return;
}
