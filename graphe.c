#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"


/*! @brief Cette fonction permet de crée un graphe
 *  @param vertices Le nombre de sommets à initialiser
 *  @param is_oriented Le graphe est orienter ou non (Booléen)
 * 
 * Comportement :
 * Initialise dans la mémoire le graphe lui affecte vertices et is_oriented,
 * Initialise les listes d'adjacences de chaques sommets sous forme de tableau
 * Puis a l'aide d'une boucle donne comme valeurs par défault 1 2 3 ... aux noeuds
 * Et NULL à la liste de noeuds voisins
 */
graph_t *create_graph(int vertices, Bool is_oriented) {
    graph_t *g = malloc(sizeof(graph_t)); // Initialise le graph

    g->is_oriented = is_oriented; // Setup le booléen
    g->nb_vertices = vertices; // Setup le nombres de sommet

    g->tab = malloc(vertices * sizeof(adjencyList_t)); // Initialise la liste de noeuds voisins pour chaque noeuds

    for (int i = 0; i < g->nb_vertices; ++i) {
        g->tab[i].data = i+1; // Par défault le noms de base des points sera 1 2 3 ...
        g->tab[i].begin = NULL; // Par défault ils n'ont pas d'arête entre eux
    }

    return g;
}

/*! @brief Fonction qui permet d'effacer un graphe de la mémoire
 *  @param g Un pointeur vers le graphe à effacer
 *  
 * Comportement :
 * On parcours tout les sommets du tableau de listes d'adjacences avec une boucle.
 */
void erase_graph(graph_t* g) {

    for (int i = 0; i < g->nb_vertices; ++i) { // Parcours chaques sommets du graphes
        node_t* current = g->tab[i].begin; // Regarde la liste d'adjacences de chaque sommets
        while (current) { // Parcours la liste d'adjacence
            node_t* tmp = current->next; // Permet d'aller d'un élément à un autre tout en sauvegardant
            // Le premier élément dans un élément temporaire
            free(current); // Free l'élément d'avant
            current = tmp; // Passe à l'élément suivant
        }
    }

    free(g->tab); // Libère le tableau avec les listes d'adjacences 

    free(g); // Libère le graphe
}

/*! @brief Permet de savoir si un graphe est vide
 *  @param g Pointeur vers le graphe
 *  
 * Comportement : 
 * Retourne true si le graph est Vide false sinon
 */
Bool is_empty(graph_t *g) {
    return g==NULL;
}

/*! @brief Vérifie l'existance d'un noeud dans le graphe
 *  @param g Un pointeur vers le graphe
 *  @param target La valeur du noeud cible
 * 
 * Comportement :
 * Parcours le tableau de listes d'adjacences et compare chaque sommet à la cible.
 * Si on rencontre la cible alors le graphe la contient on retourne l'index de la cible.
 * Sinon retourne -1 pour signifier que l'on à pas rencontré la cible.
 */
int contain(graph_t *g, int target) {
    for (int i = 0; i < g->nb_vertices; ++i) { // Boucle permettant de parcourir les sommets
        if (g->tab[i].data == target) { // Si on rencontre la cible
            return i; // On retourne l'index de la cible
        }
    }

    return -1; // Si on ne rencontre jamais la cible on retourne -1
}

/*! @brief Ajoute un sommets à un graphe
 *  @param g Un pointeur vers le graphe
 *  @param vertex La valeur du nouveau sommets
 * 
 * Comportement :
 * Premiérement actualise le nombre de sommets du graphe.
 * Réallou la taille du tableau de listes d'adjacences avec le une liste d'adjacence en plus.
 * Puis crée le nouveau sommets en l'étiquettant et en lui signifiant qu'il n'est relié à rien.
 */
graph_t *add_vertex(graph_t *g, int vertex) {
    g->nb_vertices += 1; // Agrandis le nombres de sommets de 1
    
    g->tab = realloc(g->tab, g->nb_vertices * sizeof(adjencyList_t));
    //Réalloue la mémoire du tableau de listes d'adjacences
    
    g->tab[g->nb_vertices - 1].data = vertex; // Etiquette le nouveau sommet
    g->tab[g->nb_vertices - 1].begin = NULL; // Vue qu'il est nouveau
    //Pas de lien pour l'instant donc NULL
    
    return g;
}


/*! @brief Permet de supprimer un sommet précis
 *  @param g Un pointeur vers le graphe
 *  @param target La valeur de la cible
 * 
 * Comportement :
 * Dans un premier temps vérifie que le noeuds est dans l'arbre.
 * Puis efface à tous les noeuds de la listes d'adjacences avec
 * une boucle. Ensuite inverse le dernière élément et l'élément cible
 * pour pouvoir enfin realloc le tableau avec un sommets de moins en taille.
 * Puis actualise le tableau et retourne le graphe.
 */
graph_t *remove_vertex(graph_t *g, int target) {

    int indexTarget = contain(g,target); // Vérifie que le noeud est dans le graphe

    if (indexTarget == -1) { // Si le graphe ne contient pas le noeud
        return g; // Retourne le graphe sans changement
    }

    node_t *ptr = g->tab[indexTarget].begin;
    while (ptr) { // Parcours la liste d'adjacence
        node_t* tmp = ptr->next; // Permet d'aller d'un élément à un autre tout en sauvegardant
        // Le premier élément dans un élément temporaire
        free(ptr); // Free l'élément d'avant
        ptr = tmp; // Passe à l'élément suivant
    }

    adjencyList_t tmp = g->tab[g->nb_vertices-1]; // Mémorise le dernière éléments
    g->tab[g->nb_vertices-1] = g->tab[indexTarget]; // Affecte la cible en tant que dernière élément
    g->tab[indexTarget] = tmp; // L'élément mémoriser prend la place de la cible

    g->tab = realloc(g->tab, (g->nb_vertices - 1) * sizeof(adjencyList_t)); // Réalloc la taille du tableau
    g->nb_vertices -= 1; // Actualise le nombre de sommets dans le tableau

    return g;
}

/*! @brief Permet d'ajouter une arête entre deux noeuds
 *  @param g Un pointeur vers le graphe
 *  @param src La valeur de la source
 *  @param dst La valeur de la destination
 *  @param weight Le poid de la futur arête
 * 
 * Comportement :
 * Dans un premier temps vérifie que la source est la destination
 * sont toutes deux présentes dans le graphe. Si ce n'est pas le cas
 * renvoie une erreur. Sinon crée un nouveau noeud avec comme valeur 
 * la valeur de l'étiquette de la destination. Et comme poid le poid donnée en argument.
 * Ensuite affecte ce noeuds en à la fin de la listes chaînées de noeuds adjacents.
 * Si le graphe n'est pas orienté alors réalise la même opération mais dans le sens inverse.
 */
graph_t *add_edge(graph_t* g, int src, int dst, int weight) {
    int indexSrc = contain(g,src); // Vérifie que la source est dans le graphe
    int indexDst = contain(g,dst); // Vérifie que la destination est dans le graphe
    if (indexSrc == -1 || indexDst == -1) { // Si l'un des deux n'est pas dans le graphe
        printf("Erreur : Sommet invalide\n"); // Renvoie une erreur
        return g; // Et retourne le graphe sans changement
    }

    // Créer un nouveau noeud pour la liste d'adjacence du sommet source
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = dst; // Initialise l'étiquette avec la valeur de dst
    newNode->next = NULL; // Pas d'élément après par défault
    newNode->weight = weight; // Attribue le poids pour l'arête mis en arguments

    if (g->tab[indexSrc].begin == NULL) { // Si la liste chainée est vide
        g->tab[indexSrc].begin = newNode; // Ajoute le noeud en tête
    } else { // Sinon
        node_t* current = g->tab[indexSrc].begin; // Initialise un pointeur en tête de liste
        while (current->next) { // Parcours la liste jusqu'aux dernières éléments non NULL
            current = current->next;
        }
        current->next = newNode; // Attribue comme élément suivant le nouveau noeuds
    }

    // Si le graphe n'est pas orienté on ajoute l'arête inverse
    if (!g->is_oriented) {
        // Créer un nouveau noeud pour la liste d'adjacence du sommet destination
        newNode = (node_t*)malloc(sizeof(node_t)); // reset le noeuds
        newNode->data = src; // Comme étiquette on met src
        newNode->next = NULL; // NULL par défault
        newNode->weight = weight; // On attribue le même poids que dans l'autre sens

        // De la même manière qu'avant ajoute le noeuds à la liste chainée de noeuds
        // adjacents
        if (g->tab[indexDst].begin == NULL) {
            g->tab[indexDst].begin = newNode;
        } else {
            node_t* current = g->tab[indexDst].begin;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    return g; // Retourne le graphe après les changements
}

/*! @brief Permet de supprimer une arête entre deux points
 *  @param g Un pointeur vers le graphe
 *  @param src La valeur de la source
 *  @param dst La valeur de la destination
 * 
 * Comportement : 
 * Dans un premiers temps vérifie que la source et la destination son bien dans le graphe.
 * Ensuite parcours la liste d'adjacence de la source à la recherche de la destination.
 * Si on ne trouve pas la destination on retourne une erreur sinon on supprime la destination de la liste.
 * Si le graphe n'est pas orienté répète l'opération dans le sens inverse.
 */
graph_t *remove_edge(graph_t* g, int src, int dst) {
    int indexSrc = contain(g,src); // Vérifie que la source est dans le graphe
    int indexDst = contain(g,dst); // Vérifie que la destination est dans le graphe
    if (indexSrc == -1 || indexDst == -1) { // Si l'un des deux n'est pas dans le graphe
        printf("Erreur : Sommet invalide\n"); // Renvoie une erreur
        return g; // Et retourne le graphe sans changement
    }

    node_t* current = g->tab[indexSrc].begin; // Pointeur sur la tête de listes
    // de sommet adjacents
    node_t* prev = NULL; // Initialise un pointeur pour mémorise le noeud d'avant

    while (current != NULL && current->data != dst) { // Tant que on ne rencontre pas le noeuds
                                                      // ou que la liste n'est pas vide
                                                      // on parcours cette dernière
        prev = current; 
        current = current->next;
    }

    if (current == NULL) { // Si current est NULL on n'a pas trouvé le lien
        printf("Arête non trouvée src->dst \n"); // Donc retourne une erreur
        return g; // Et le graphe inchangé
    }

    if (prev == NULL) { // Si on supprime la tête
        g->tab[indexSrc].begin = current->next; // Alors l'élément d'après devient la tête
    } else { // Sinon
        prev->next = current->next; // Raccorde l'élément avant et après
    }

    free(current); // Et enfin dans les deux cas supprime la cible

    // Si le graphe est non orienté on fait le même procéder mais dans le sens inverse
    if (!g->is_oriented) {
        current = g->tab[indexDst].begin;
        prev = NULL;

        while (current != NULL && current->data != src) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            printf("Arête inverse non trouvée dst->src \n");
            return g;
        }

        if (prev == NULL) {
            g->tab[indexDst].begin = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }

    return g;
}

/*! @brief Permet d'afficher un graphe
 *  @param g Un pointeur vers le graphe
 * 
 * Comportement : 
 * Premièrement on vérifie si le graphe est NULL si oui on retourne <empty>.
 * Sinon on parcours le tableau de listes d'adjacences avec une boucle en affichant dans 
 * un premier temps le noeud puis ces fils à l'aide d'un while parcourant la liste chainées représentant
 * les noeuds adjacents.
 */
void display_graphe(graph_t *g) {

    if (g == NULL) {
        printf("\n<empty>");
        return;
    }

    printf("\n\n  Le graphe : ");
    for (int i = 0; i < g->nb_vertices; ++i) { // Parcours chaques sommets du graphes
        printf("\n (%d) : ",g->tab[i].data);

        node_t* ptr = g->tab[i].begin; // Regarde la liste d'adjacences de chaque sommets

        if (!ptr) {
            printf("rien");
        }

        while (ptr) { // Parcours la liste d'adjacence
            printf("%d (poids %d)",ptr->data,ptr->weight);
            if (ptr->next) printf(", ");
            ptr = ptr->next; // Passe à l'élément suivant
        }
    }

}

//algorithme de djisktra
//parcours en largeur
//parcours en profondeur
