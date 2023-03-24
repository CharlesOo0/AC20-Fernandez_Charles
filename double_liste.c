#include "double_liste.h"

/*!
 * @brief Libère la mémoire de tous les éléments de la liste chaînée
 * @param head l'adresse du premier élément de la liste
 */
void erase_list_dl(liste_double_t* head){

    while (head->next) {
        head = head->next;
        free(head->previous); 
    }

    free(head);


}

/*!
 * @brief Affiche une liste chainée
 * @param head le pointeur sur le premier élément de la liste
 *
 * Comportement attendu :
 *  - si head est NULL : afficher <empty>
 *  - sinon : afficher le contenu de la liste
 */
void display_list_dl(liste_double_t* head) {
    liste_double_t *ptr = head;

    if (head == NULL) { // Si la liste est vide alors on affiche <empty>
        printf("<empty>\n\n"); // ne pas oublier le \n pour éviter une sortie sur une seule ligne
        return;
    }

    printf("Liste chainée :\n( ");
    while (ptr != NULL) { // On itère à travers la liste chainées jusqu'aux dernières élément non NULL
        printf("%d ",ptr->data);
        ptr = ptr->next; // Passe d'un élément à un autre
    }
    printf(")\n\n");
    return;
}

/*!
 * @brief Ajoute une node en tête de liste
 * @param head pointeur vers la tête de liste
 * @param data la data de la nouvelle node
 * 
 * Comportement :
 * - Crée un nouvelle élément lui affecte comme élément suivant
 * - la liste en argument et comme data la data en argument
 */

liste_double_t* add_head_dl(liste_double_t* head, int data) {

    liste_double_t* new_node = malloc(sizeof(liste_double_t)); // Initialise le nouvelle élément
    new_node->next = head; // Affecte le reste de la liste comme élément suivant
    new_node->data = data; // Affecte la donnée
    new_node->previous = NULL;
    if (head) {
        head->previous = new_node; // Affecte comme node précédente le nouvelle élément
    }
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
liste_double_t *add_tail_list_dl(liste_double_t* head, int data){
    liste_double_t *new_node = (liste_double_t *) malloc(sizeof(liste_double_t)); // Initialise la mémoire du nouvelle élément -> pas d'* dans sizeof
    
    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = NULL;


    if (head == NULL) { // Si la liste est vide alors le nouvelle élément est la tête
        new_node->previous = NULL;
        head = new_node;
    } else {
        liste_double_t *ptr = head;
        while (ptr->next) { // Pas besoin de vérifier que ptr est !=NULL (pour permettre ptr->next sans plantage) : on le sait car dans le else de head==NULL (et head==ptr)
            ptr = ptr->next;
        }
        ptr->next = new_node;
        new_node->previous = ptr->next;
    }

    return head;
}


/*!
* @brief Efface le première élément de la liste
* @param head pointeur vers le première élément de la liste
*
* Comportement :
* - regarde si l'élément suivant de la tête existe si oui le retourne en tant que tête et free l'ancienne tête
* - sinon retourne NULL
* - si la tête est NULL retourne également NULL
*/
liste_double_t *delete_head_list_dl(liste_double_t* head){

    if (head && head->next) {
        liste_double_t* temp = head->next; // Nécessaire car quand on free la tête on ne peut plus récupérer l'élément suivant
        free(head); // Supprime l'ancienne tête
        return temp;
    }

    if (head) {
        free(head);
    }

    return NULL;
}

/*!
* @brief Efface le dernière élément de la liste
* @param head pointeur vers le première élément de la liste
*
* Comportement :
* - on itère jusqu'a l'avant dernière élément de la liste
* - puis efface le dernière élément et affecte à l'avant dernière élément la valeur NULL
* - à la toute fin on retourne la tête de liste
* - Cas spécial 1 : la liste est NULL alors on retourne NULL
* - Cas spécial 2 : il y a un seul élément dans la liste alors on le supprime et renvoie NULL
*/
liste_double_t *delete_tail_list_dl(liste_double_t* head){
    liste_double_t* ptr = head; // Initialise un pointeur sur la tête

    if (!head) { // Si la liste est NULL rien à effacer retourne NULL
        return NULL;
    }

    if (head && !head->next) { // Si la liste à un seul élément on free cet élément et on retourne NULL
        free(head); // Efface le seul élément de la liste
        return NULL;
    }

    while (ptr->next->next) { // Itère jusqu'a l'avant dernière élément de la liste
        ptr = ptr->next;
    }

    free(ptr->next); // Efface le dernière élément
    ptr->next = NULL;

    return head;
}
