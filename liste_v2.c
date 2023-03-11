#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste_v2.h"

/*! 
 * @brief Libère toute les cases mémoire d'une liste chainée et de ça fiche propriété
 * @param propriete pointeur vers la fiche propriété de la liste
 */

void erase_list_v2(liste_propriete_t* propriete) {

    liste_chainee_t *temp = propriete->head;
    while (propriete->head) {
        temp = propriete->head;
        propriete->head = propriete->head->next;
        free(temp);
    }

    propriete->list_length = 0;

    return;
}

/*!
 * @brief Ajout d'un élément en tête de liste
 * @param propriete vers la fiche propriété de la liste
 * @param data la data du nouvelle élément de la liste
 * 
 * Comportement : 
 * Crée un nouvelle élément et l'ajoute en tête de liste
 */
liste_chainee_t *add_head_list_v2(liste_propriete_t* propriete, int data) {
    liste_chainee_t *new_node = (liste_chainee_t*)malloc(sizeof(liste_chainee_t)); // Crée la nouvelle node

    new_node->data = data; // Affecte la data à la nouvelle node
    new_node->next = propriete->head; // La nouvelle node pointe sur l'ancienne tête

    propriete->list_length += 1; // Ajoute 1 à la taille de la liste sur la fiche propriété
    if (!propriete->head) { // Si la tete de liste est NULL alors il n'y à pas non plus de queue logique
        propriete->tail = new_node;
    }

    return new_node;
}

/*! 
 * @brief Ajoute un élément en fin de liste
 * @param propriete pointeur vers la fiche propriete de la liste
 * @param data la data du nouvelle élément
 * 
 * Comportement : 
 * - Crée un nouvelle élément et l'affecte en fin de liste
 * - Puis change les caractéristique affecté de la fiche propriété
 */
liste_chainee_t *add_tail_list_v2(liste_propriete_t* propriete, int data) {
    liste_chainee_t* new_node = (liste_chainee_t*)malloc(sizeof(liste_chainee_t)); // Crée le nouvelle élément
    new_node->next = NULL;
    new_node->data = data;

    propriete->list_length += 1; // Ajoute 1 à la taille de la liste sur la fiche propriété
    propriete->tail->next = new_node; // Affecte le nouvelle élément en fin de liste
    propriete->tail = new_node; // Le nouvelle élément devient la nouvelle queue de liste

    if (propriete->list_length == 1) { // Si il y à un seul élément dans la liste alors la queue est aussi la tête
        return new_node;
    }

    return propriete->head;
}

/*!
 * @brief Affiche une liste 
 * @param propriete pointeur vers la fiche propriété de la liste
 * 
 * Comportement : 
 * - Si la liste est NULL affiche <empty> et les caractéristiques de la fiche propriété
 * - Sinon affiche la liste et les caractéristiques de la fiche propriété
 */

void display_list_v2(liste_propriete_t *propriete) {

    if (propriete->head == NULL) { // Si la liste est vide alors on affiche <empty>
        printf("<empty>\n"); // ne pas oublier le \n pour éviter une sortie sur une seule ligne
        display_property(propriete);
        return;
    }

    liste_chainee_t *ptr = propriete->head;

    printf("Liste chainée :\n( ");
    // Pour le while, même convention syntaxique que if
    while (ptr != NULL) { // On itère à travers la liste chainées jusqu'aux dernières élément non NULL
        printf("%d ",ptr->data);
        ptr = ptr->next; // Passe d'un élément à un autre
    }
    printf(")\n");
    display_property(propriete);
    return;
}

/*!
 * @brief Affiche les caractéristique d'une fiche propriété
 * @param propriete un pointeur vers une fiche propriété
 * 
 * Comportement : 
 * -Affiche la data de la tête et de la queue si elle existe
 * -et la taille de la liste
 */
void display_property(liste_propriete_t* propriete) {

    if (propriete->head) {
        printf("Head : %d, Tail : %d, List length : %d\n\n",propriete->head->data,propriete->tail->data,propriete->list_length); //Affiche toutes les caractéristiques valeurs tete 
        return; // et queue comprise si elles existes
    }

    printf("Head :  NULL, Tail : NULL, List length : %d\n\n",propriete->list_length); // Si valeurs tête et queue n'existe pas alors affiche NULL
    return;
}

/*!
 * @brief Efface l'élément en tête de liste
 * @param propriete pointeur vers la fiche propriete de la liste
 *
 * Comportement :
 * Efface la tête et lui affecte l'élément suivant s'il existe
 * Si la tête n'existe pas la liste est déjà vide alors ne fait rien
 */
liste_chainee_t *delete_head_list_v2(liste_propriete_t* propriete) {

    if (!propriete->head) { // Traite le cas ou la liste est vide
        return NULL;
    }

    if (propriete->list_length == 1) { // Traite le cas ou il y à un seul élément dans la liste
        free(propriete->head);
        return NULL;
    }

    liste_chainee_t *tmp = propriete->head->next; // Ne pas perdre la variable après la tête
    free(propriete->head); // Efface la tête
    propriete->list_length -= 1; // Enleve 1 à la taille de la liste

    return tmp;
}


/*!
 * @brief Efface le dernière élément de la liste
 * @param propriete un pointeur vers la fiche propriété de la liste
 *
 * Comportement : 
 * -Efface le dernière élément de la liste s'il existe
 */

liste_chainee_t *delete_tail_list_v2(liste_propriete_t* propriete){
    liste_chainee_t* ptr = propriete->head; // Initialise un pointeur sur la tête

    if (!propriete->head) { // Si la liste est NULL rien à effacer retourne NULL
        return NULL;
    }

    if (propriete->head && !propriete->head->next) { // Si la liste à un seul élément on free cet élément et on retourne NULL
        propriete->list_length -= 1;
        free(propriete->head); // Efface le seul élément de la liste
        return NULL;
    }

    while (ptr->next->next) { // Itère jusqu'a l'avant dernière élément de la liste
        ptr = ptr->next;
    }

    propriete->list_length -= 1;
    free(ptr->next); // Efface le dernière élément
    ptr->next = NULL;

    return propriete->head;
}
