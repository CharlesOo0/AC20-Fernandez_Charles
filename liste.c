#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

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
        printf("<empty>\n\n"); // ne pas oublier le \n pour éviter une sortie sur une seule ligne
        return;
    }

    //ptr = head; // On initialise le pointeur en tête de liste -> inutile car fait à la déclaration de ptr

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

/*!
* @brief retourne le nombre d'élément d'une liste chainée
* @param head le pointeur sur le premier élément de la liste
* 
* Comportement :
* - Itère simplement dans la liste jusqu'au dernière élément et compte
*/
int list_length(liste_chainee_t* head){
    int i = 0;
    liste_chainee_t* ptr = head; // Initialise un pointeur sur la tête de liste

    while (ptr) { // Itère dans la liste
        ptr = ptr->next;
        ++i;
    }

    return i;
}

/*!
* @brief Ajout d'un élément à une position donnée
* @param head le pointeur sur le première élément de la liste
* @param data la donnée du nouvelle élément à ajouté
* @param pos la position ou il faut rajouté l'élément
*
* Comportement :
* - la fonction alloue la mémoire pour un nouvelle élément de la liste chainée
* - dans un premier temps on regarde si la position choisi par l'utilisateur reste dans l'environnement de la liste
* - on parcours la liste jusqu'a l'élément avant la position que l'on cherche à insérer appelons le "ptr"
* - on retien l'élément après "ptr", appelons celui-ci "temp"
* - on affecte à l'élément suivant de "ptr" notre nouvelle élément
* - on affecte "temp" comme élément suivant de notre nouvelle élément 
* - Cas spécial 1 : la liste est vide dans ce cas la on affecte à head notre nouvelle élément
* - Cas spécial 2 : la position choisi est 0 dans ce cas là on utilise la même facon d'agir que dans add_head_list()
*/
liste_chainee_t *add_target_list(liste_chainee_t* head, int data, int pos){
    liste_chainee_t *new_node = (liste_chainee_t *) malloc(sizeof(liste_chainee_t));
    
    new_node->data = data; // Ajoute la data au nouvelle élément
    new_node->next = NULL;

    if (pos > list_length(head) || pos < 0) {  // Controle d'acquisition
        printf("Erreur l'élément n'a pas était ajouté car la position choisi est incorrecte.\n");
        return head;
    }

    if (head == NULL) { // Si la liste est vide alors le nouvelle élément est la tête
        head = new_node;
    }else if (head && pos == 0) { // Si on cherche à affectée au première élément alors notre nouvelle élément devient la tête
        new_node->next = head;
        return new_node;
    }else {
        liste_chainee_t *ptr = head;
        int i = 0;
        while (ptr->next && i < pos - 1) { // Itere jusqu'à l'élément avant la position de l'élément que l'on cherche à insérer
            i++;
            ptr = ptr->next;
        }

        liste_chainee_t *temp = NULL;
        if (ptr->next) { // Récupère l'élément après l'élément que l'on insère
            temp = ptr->next;
        }
        ptr->next = new_node; // Place le nouvelle élément au bonne endroit de la liste
        new_node->next = temp; // Colle au nouvelle élément le reste de la liste
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
liste_chainee_t *delete_head_list(liste_chainee_t* head){

    if (head && head->next) {
        liste_chainee_t* temp = head->next; // Nécessaire car quand on free la tête on ne peut plus récupérer l'élément suivant
        free(head); // Supprime l'ancienne tête
        return temp;
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
liste_chainee_t *delete_tail_list(liste_chainee_t* head){
    liste_chainee_t* ptr = head; // Initialise un pointeur sur la tête

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


/*!
* @brief Efface un élément à une position de la liste
* @param head Un pointeur vers le première élément de notre liste
* @param pos La position de l'élément que l'on souhaite supprimer
*
* Comportement :
* - dans un premier on vérifie que la valeur donnée de "pos" est bien dans l'environnement de la liste
* - ensuite On itère dans la liste avec pointeur jusqu'à l'élément avant la position voulue
* - si il y à un élément après l'élément que l'on souhaite supprimer alors
* - on sauvegarde ce dernier dans une variable temporaire
* - on supprime l'élément voulue et on le recolle au premier bout de liste
* - sinon on supprime simplement l'élément voulue
* - à la fin on retourne un pointeur sur la tête de liste
* - Cas spécial 1 : la liste est vide alors on retourne NULL
* - Cas spécial 2 : On supprime le première élément alors on supprime la tête et renvoie l'élément d'après si il existe
*/

liste_chainee_t *delete_target_list(liste_chainee_t* head, int pos){

    if (pos > list_length(head)-1 || pos < 0) {  // Controle d'acquisition
        printf("Erreur l'élément n'a pas était supprimé car la position choisi est incorrecte.\n");
        return head;
    }

    if (!head) { // Si la liste est NULL renvoie NULL
        return NULL;
    }else if (head && pos == 0) { // Si il y à un seul élément dans la liste le supprime donc renvoie NULL
        if (head->next) {
            liste_chainee_t* temp = head->next;
            free(head);
            return temp;
        }
        return NULL;
    }

    liste_chainee_t* ptr = head; // Initialise un pointeur pour itérer dans la liste
    int i = 0;
    while (ptr->next && i < pos-1) { // Itère jusqu'à l'élément avant celui que l'on cherche à supprimer
        ptr = ptr->next;
        ++i;
    }

    liste_chainee_t* temp = ptr->next; // Copie de la case mémoire à supprimer necessaire car on va la reaffacter
    if (ptr->next->next) { // Vérifie s'il y à un autre bout de liste après l'élément que l'on veux supprimer
        ptr->next = ptr->next->next; // Si oui le colle au premier bout
        free(temp); // Efface l'élément voulue
        return head;
    }
    
    free(temp); // Efface l'élément voulue
    ptr->next = NULL;
    return head;
}
