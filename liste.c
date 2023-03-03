#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

/* Efface une liste chainées */
/*!
 * @brief Libère la mémoire de tous les éléments de la liste chaînée
 * @param head l'adresse du premier élément de la liste
 */
void erase_list(liste_chainee_t* head){
    //liste_chainee_t *temp = (liste_chainee_t*)malloc(sizeof(liste_chainee_t*)); // voir display_list pour l'erreur sur cette ligne

 /* if( head == NULL ){ Code inutile : le while (head) va sortir directement si head est NULL
        return;
    }
*/
    liste_chainee_t *temp = head;
    while (head != NULL) { // Peut s'écrire while (head) {...
        temp = head;
        head = head->next;
        free(temp);
    }
//    return; Inutile, à la fin, une fonction retournant void retourne automatiquement
}

/*!
 * @brief Affiche une liste chainée
 * @param head le pointeur sur le premier élément de la liste
 *
 * Comportement attendu :
 *  - si head est NULL : afficher <empty>
 *  - sinon : afficher le contenu de la liste
 */
void display_list(liste_chainee_t* head) {
    // La ligne ci-dessous (1) n'initialise pas un pointeur. Elle réserve de la mémoire, dont elle retourne la valeur.
    // Cette valeur retournée est ensuite utilisée pour initialiser la valeur du pointeur ptr
    // L'initialisation d'un pointeur peut se faire de différentes manières, du moment qu'on lui affecte une adresse mémoire :
    // - NULL (pas de cible du pointeur)
    // - la valeur d'un autre pointeur (qui peut, mais pas nécessairement, être un retour de fonction comme malloc)
    // - l'adresse d'une variable, obtenue avec & (par ex. pour la variable nommée var, on obtient son adresse avec &var)
    // (1) liste_chainee_t *ptr = (liste_chainee_t*)malloc(sizeof(liste_chainee_t*)); // Initialise un pointeur sur la liste à afficher
    
    // Dans notre cas, on veut initialiser ptr à la valeur du début de la liste, donc head.
    liste_chainee_t *ptr = head;

    // Convention pour la syntaxe : un espace entre if et les (), pas d'espace entre les () et leur contenu,
    // des espaces entre les opérateurs, et un espace entre la ) et {, puis saut de ligne
    if (head == NULL) { // Si la liste est vide alors on affiche <empty>
        printf("<empty>\n"); // ne pas oublier le \n pour éviter une sortie sur une seule ligne
        return;
    }

    //ptr = head; // On initialise le pointeur en tête de liste -> inutile car fait à la déclaration de ptr
    //int i = 1; // i est une variable inutile

    printf("Liste chainée :\n( ");
    // Pour le while, même convention syntaxique que if
    while (ptr != NULL) { // On itère à travers la liste chainées jusqu'aux dernières élément non NULL
        printf("%d ",ptr->data);
        ptr = ptr->next; // Passe d'un élément à un autre
    }
    printf(")\n\n");
    return;
}

// Remarque pour les deux fonctions add : on transmet un simple pointeur et c'est la fonction appelante qui refait l'affectation de la nouvelle tête
// de liste à sa variable pointant sur la liste (une_liste dans mes exemples du main)

/*!
 * @brief Ajout d'un élément en tête de liste
 * @param head le pointeur sur le premier élément de la liste
 * @param data la valeur du nouvel élément à ajouter en tête
 *
 * Comportement :
 * - la fonction alloue la mémoire pour une nouvelle structure de type liste_chainee
 * - Cette nouvelle structure est ajoutée à la liste : son pointeur next pointe vers l'ancienne tête désignée par head
 * - la fonction retourne l'adresse de cette nouvelle structure pour que l'appelant (fonction qui a appelé add_head_list)
 *   affecte cette valeur à sa variable pointant sur la liste.
 */
liste_chainee_t *add_head_list(liste_chainee_t* head, int data){
    liste_chainee_t *new_node = (liste_chainee_t *) malloc(sizeof(liste_chainee_t)); // Initialise la mémoire du nouvelle élément: pas d'étoile dans sizeof, sinon type incorrect

    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = head; // La tête devient l'élément suivant du nouvelle élément
    //*head = new_node;       // on ne modifie plus le paramètre, mais on retourne le pointeur sur le nouveau 1er élément

    return new_node;
}

/*!
 * @brief Ajout d'un élément en fin de liste
 * @param head le pointeur sur le premier élément de la liste
 * @param data la valeur du nouvel élément à ajouter en tête
 *
 * Comportement :
 * - la fonction alloue la mémoire pour une nouvelle structure de type liste_chainee
 * - on parcourt la liste jusqu'à l'avant dernier élément (ptr != NULL mais ptr->next == NULL)
 * - on fait pointer ptr->next vers la nouvelle structure
 * - on retourne la valeur de head que l'appelant affectera à sa variable pointant sur la liste.
 * - Cas spécial : la liste est vide : on alloue la mémoire, on l'affecte à head et on retourne head
 */
liste_chainee_t *add_tail_list(liste_chainee_t* head, int data){
    liste_chainee_t *new_node = (liste_chainee_t *) malloc(sizeof(liste_chainee_t)); // Initialise la mémoire du nouvelle élément -> pas d'* dans sizeof
    
    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = NULL;

    if (head == NULL) { // Si la liste est vide alors le nouvelle élément est la tête
        head = new_node;
    } else {
        liste_chainee_t *ptr = head;
        while (ptr->next) { // Pas besoin de vérifier que ptr est !=NULL (pour permettre ptr->next sans plantage) : on le sait car dans le else de head==NULL (et head==ptr)
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }

    return head;
}
