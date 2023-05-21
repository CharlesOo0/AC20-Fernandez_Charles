#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "graphe.h"


/*! @brief Cette fonction permet de crée un graphe
 *  @param vertices Le nombre de sommets à initialiser
 *  @param is_oriented Le graphe est orienter ou non (Booléen)
 * 
 * Comportement :
 * Initialise dans la mémoire le graphe lui affecte vertices et is_oriented,
 * Initialise les listes d'adjacences de chaques sommets sous forme de tableau
 * Et de chaques case mémoire en plus du tableau (cf commentaires)
 * Puis a l'aide d'une boucle donne comme valeurs par défault 1 2 3 ... aux noeuds
 * allouée et NULL aux noeuds non allouées.
 * Et NULL à la liste de noeuds voisins de chaque noeuds.
 */
graph_t *create_graph(int vertices, bool is_oriented) {
    graph_t *g = malloc(sizeof(graph_t)); // Initialise le graph

    g->is_oriented = is_oriented; // Setup le booléen
    g->memory_allocated = vertices; // La mémoire allouer du tableau est égale aux nombres de noeuds
    g->tab_memory = 10 + (vertices/10) * 10;

    g->tab = malloc( g->tab_memory * sizeof(adjencyList_t)); // Initialise la liste de noeuds voisins pour chaque case mémoire du tableau
    // Donc un tableau sera de taille 10 par défault et on rajoutera 10  à ca taille pour chaque pour chaque dizaine de noeuds en plus
    // Exemple :
    // Si 10 noeuds -> mémoire du tableau = 20
    // Si 11 noeuds -> mémoire du tableau = 20
    // Si 55 noeuds -> mémoire du tableau = 60

    for (int i = 0; i < g->memory_allocated; ++i) { // Boucle pour intialiser seulement la mémoire allouer du tableau
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

    for (int i = 0; i < g->memory_allocated; ++i) { // Parcours chaques sommets du graphes
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
bool is_empty(graph_t *g) {
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
    for (int i = 0; i < g->memory_allocated; ++i) { // Boucle permettant de parcourir les sommets
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
 * Ensuite vérifie si la mémoire allouée à atteint la mémoire maximale du tableau
 * Si oui utilise increase_memory pour augmenter la taille du tableau de 10 unités
 * Puis ajoute le nouveau sommets.
 */
graph_t *add_vertex(graph_t *g, int vertex) {

    if (contain(g,vertex) != -1) {
        printf("Le graphe contient déjà le noeud");
        return g;
    } 

    g->memory_allocated += 1; // Agrandis le nombres de sommets de 1
    
    if (g->memory_allocated >= g->tab_memory) {
        g->tab = increase_memory(g);
        //Réalloue la mémoire du tableau de listes d'adjacences en ajoutant 10
    }
    
    g->tab[g->memory_allocated - 1].data = vertex; // Etiquette le nouveau sommet
    g->tab[g->memory_allocated - 1].begin = NULL; // Vue qu'il est nouveau
    //Pas de lien pour l'instant donc NULL
    
    return g;
}


/*! @brief Permet d'augmenter la taille mémoire d'un tableau de 10 unités
 *  @param g Un pointeur vers le graphe
 *
 * Comportement :
 * Initialise un nouveau tableau avec comme taille +10 unités de valeurs que l'ancien.
 * Copie à l'aide d'une boucle la partie allouée de la mémoire de l'ancien tableau dans le nouveau.
 * Libère de la mémoire l'ancien tableau et retourne le nouveau
 */
adjencyList_t *increase_memory(graph_t* g) {
    g->tab_memory += 10;
    adjencyList_t *new_tab = malloc( g->tab_memory * sizeof(adjencyList_t) ); // Initialise le nouveau tableau

    for (int i = 0; i < g->memory_allocated ; ++i) { // Copie l'ancien tableau dans le nouveau tableau
        new_tab[i].data = g->tab[i].data; // Copie le nom du noeuds
        new_tab[i].begin = g->tab[i].begin; // Copie la liste de ces voisins
    }
    
    free(g->tab); // Libère de la mémoire l'ancien tableau

    return new_tab; // Retourne le nouveau tableau pour l'affecter
}


/*! @brief Permet de supprimer un sommet précis
 *  @param g Un pointeur vers le graphe
 *  @param target La valeur de la cible
 * 
 * Comportement :
 * Dans un premier temps vérifie que le noeuds est dans l'arbre.
 * Ensuite avec une boucle parcours les listes d'adjacences de tout les noeuds
 * du graphes et vérifie si le noeuds cible est présent si oui on l'efface de la liste d'adjacences.
 * Puis on parcours la liste d'adjacences du noeuds cible pour la libérer entièrerement de la mémoire.
 * Ensuite on inverse le noeud cible avec le dernière élément du tableau de sommets. Et on enlèvre 1
 * à la mémoire allouée, si cette le tableau à 11 cases mémoires innocupées et qu'il à aux moins 20 case mémoires
 * on lui enlève 10 cases mémoires à l'aide de reduce_memory.
 */
graph_t *remove_vertex(graph_t *g, int target) {

    int indexTarget = contain(g,target); // Vérifie que le noeud est dans le graphe

    if (indexTarget == -1) { // Si le graphe ne contient pas le noeud
        return g; // Retourne le graphe sans changement
    }

    node_t *before = NULL; // Initialise un pointeur pour mémorise le noeud avant ptr
    node_t *ptr = NULL; // Initialise un pointeur pour parcourir la liste d'adjacence
    for (int i = 0; i < g->memory_allocated; ++i) { // Boucle à travers tout les sommets du tableau
        before = NULL; // Pas de noeud avant le premier noeud logique
        ptr = g->tab[i].begin; // Récupère le premier noeud voisins du sommets
        while (ptr) { // Tant qu'il y à des voisins
            if (ptr->data == target) { // Si on trouve le noeud cible
                if (before) { // Et qu'il n'est pas la tête de liste
                    before->next = ptr->next; // On enlève le noeud de la liste
                }else { // Et qu'il est la tête de liste
                    g->tab[i].begin = ptr->next; // On affecte le noeud d'après en tant que tête
                }

                free(ptr); // Puis on libère le noeud
                break; // Sort de la boucle vue que l'on à trouver la cible
            }
            before = ptr;
            ptr = ptr->next;
        }
    }

    ptr = g->tab[indexTarget].begin;
    while (ptr) { // Parcours la liste d'adjacence
        node_t* tmp = ptr->next; // Permet d'aller d'un élément à un autre tout en sauvegardant
        // Le premier élément dans un élément temporaire
        free(ptr); // Free l'élément d'avant
        ptr = tmp; // Passe à l'élément suivant
    }

    adjencyList_t tmp = g->tab[g->memory_allocated-1]; // Mémorise le dernière éléments
    g->tab[g->memory_allocated-1] = g->tab[indexTarget]; // Affecte la cible en tant que dernière élément
    g->tab[indexTarget] = tmp; // L'élément mémoriser prend la place de la cible

     g->memory_allocated -= 1; // Actualise le nombre de sommets dans le tableau

    if (g->tab_memory - g->memory_allocated == 11  && g->tab_memory >= 20) { // Si il y à 11 cases mémoires et que le tableau à aux moins 20 cases mémoires
        g->tab = reduce_memory(g); // On peux le réduire de 10 cases mémoires
    }

    return g;
}

/*! @brief Permet d'augmenter la taille mémoire d'un tableau de 10 unités
 *  @param g Un pointeur vers le graphe
 *
 * Comportement :
 * Initialise un nouveau tableau avec comme taille -10 unités de valeurs que l'ancien.
 * Copie à l'aide d'une boucle la partie allouée de la mémoire de l'ancien tableau dans le nouveau.
 * Libère de la mémoire l'ancien tableau et retourne le nouveau
 */
adjencyList_t *reduce_memory(graph_t* g) {
    g->tab_memory -= 10;
    adjencyList_t *new_tab = malloc( g->tab_memory * sizeof(adjencyList_t) ); // Initialise le nouveau tableau

    for (int i = 0; i < g->memory_allocated ; ++i) { // Copie l'ancien tableau dans le nouveau tableau
        new_tab[i].data = g->tab[i].data; // Copie le nom du noeuds
        new_tab[i].begin = g->tab[i].begin; // Copie la liste de ces voisins
    }

    free(g->tab); // Libère de la mémoire l'ancien tableau
    
    return new_tab; // Retourne le nouveau tableau pour l'affecter
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

    node_t* ptr = g->tab[indexSrc].begin; // affecte un pointeur sur la tête de listes
    // des noeuds voisins de la source

    while (ptr) { // Parcours les voisins de la source
        if (ptr->data == dst) { // Si on rencontre la destination
            printf("Erreur les sommets sont déjà liées"); // Les noeuds sont déjà liées
            return g; // Donc met fin à la fonction
        }
        ptr = ptr->next;
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

    printf("\n\n  Le graphe : \n Mémoire allouée : %d / %d",g->memory_allocated,g->tab_memory);

    for (int i = 0; i < g->memory_allocated; ++i) { // Parcours chaques sommets du graphes
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

/*----------------------- Algorithme de Djikstra -----------------------*/

/*! @brief Cette fonction permet de récupérer l'index d'un noeud dans le tableau
 *  @param tab Pointeur vers le tableau
 *  @param target Valeur du noeud cible
 *  @param length Taille du tableau
 * 
 * Comportement :
 * Itère à travers le tableau jusqu'à trouver le noeud cible.
 * Si on le trouve retourne son index sinon retourne -1 en guise d'erreur.
 */
int getIndex(node_d_t *tab, int target, int length) {
    for (int i = 0; i < length; ++i) { // Itère à travers le tableau
        if (tab[i].data == target) { // Si on trouve la cible
            return i; // Retourne l'index
        }
    }

    return -1; // Erreur si on ne trouve pas la cible
}

/*! @brief Cette fonction permet de savoir si tout les noeuds du graphes ont était explorées
 *  @param tab Pointeur vers le tableau
 *  @param length Taille du tableau
 * 
 * Comportement :
 * Itère à travers tout les noeuds du tableau si l'on rencontre un noeud qui n'a pas était visité
 * on retourne false sinon true.
 */
bool isPainted(node_d_t *tab, int length) {
    for (int i = 0; i < length; ++i) { // Itère à travers le tableau
        if (tab[i].painted == false) { // Si un noeud n'a pas était vue
            return false; // Alors tout les noeuds ne sont pas peints
        }
    }

    return true; // Si tout les noeuds on était vue alors tout les noeuds sont peints
}


/*! @brief Cette fonction permet de trouver le prochain noeud à exploré
 *  @param tab Pointeur vers le tableau
 *  @param length Taille du tableau
 * 
 * Comportement :
 * Itère une première fois pour trouver un noeud qu'y n'a pas était visité et dont l'étiquette n'est pas infini.
 * Puis itère une deuxième fois pour chercher s'il il existe dans le tableau un noeud avec une étiquette plus petite qui n'a pas
 * était visité
 */
int searchCurrent(node_d_t *tab, int length) {
    int current = 0;
    for (int i = 0 ; i < length ; ++i) { // Itère à travers le tableau
        if (tab[i].painted == false && tab[i].nametag != -1) { // Si le noeud n'a pas était exploré
        // Et que son étiquette n'est pas infini
            current = i; // Alors ce noeud devient le current
        }
    }

    for (int i = 0 ; i < length ; ++i) { // Itère une seconde fois à travers la tableau
        if (tab[i].painted == false && tab[i].nametag != -1 && tab[i].nametag < tab[current].nametag) {
            // Si on trouve un noeud plus petit qui n'a pas une étiquette infini
            // Et qui n'a pas était visité
            current = i; // Alors ce noeud devient le current
        }
    }
    
    return current; // On retourne le noeud selectionné par les deux tris
}


/*! @brief Permet de crée le tableau de chemin de chaque noeuds
 *  @param tab Le tableau représentant chaque noeuds
 *  @param indexCurrent L'index dans le tableau du noeud actuellement traité
 *  @param indexTarget L'index du noeud sortant en train d'être traité
 * 
 * Comportement : 
 * Copie le chemin du noeud traité dans le noeud sortant. Puis rajoute au noeud
 * sortant en fin de chemin lui même tout dans augmentant la taille occupé dans la mémoire de 1.
 */
void concatene_path(node_d_t *tab, int indexCurrent, int indexTarget) {
    for (int i = 0 ; i < tab[indexCurrent].path_length ;  ++i) {
        tab[indexTarget].path[i] = tab[indexCurrent].path[i];
    }
    tab[indexTarget].path[tab[indexCurrent].path_length] = tab[indexTarget].data;
    tab[indexTarget].path_length = tab[indexCurrent].path_length + 1 ;
    return;
}


/*! @brief Implémante l'algorithme de Djikstra pour trouver le plus cour chemin
 *  @param g Un pointeur vers le graphe
 *  @param start Noeud de départ pour commencer l'algorithme
 * 
 * Comportement : 
 * Initialise un tableau de noeuds de Djikstra de la taille du nombre de noeud de graphe.
 * Puis commence par le noeud du départ regard les noeuds sortant de ce dernier à l'aide d'une boucle
 * dans ca liste d'adjacence note le poids pour atteindre les chemins si ce dernier est le poids le plus petit
 * et le noeud qui précède le noeud sortant. Ensuite cherche quel noeud analysé parmi les noeuds restants qui ne sont pas peints
 * a l'aide de searchCurrent. Puis print les résultats trouvées.
 */
void Djikstra(graph_t *g, int start) {
    node_d_t *tab = malloc(g->memory_allocated * sizeof(node_d_t)); // Alloue un tableau de la taille du nombre de noeuds
    int length = g->memory_allocated ; //
    // Initialise un tableau de noeuds de djisktra de même taille que le nombre
    // de sommets du graphe

    for (int i = 0; i < length ; ++i) { // Initialise le tableau de noeuds de djikstra
        tab[i].data = g->tab[i].data; // Récupère le nom de chaque sommets du graphe
        tab[i].painted = false; // Par défault les noeuds n'ont pas était vue
        tab[i].nametag = -1; // Par défault le poid pour y accéder est infini ici représenter par -1
        tab[i].begin = g->tab[i].begin; // Associe les noeuds voisins au nouveau tableau

        tab[i].path = malloc(g->memory_allocated * sizeof(int)); // Alloue un tableau de la taille maximale que le chemin peux prendre
        tab[i].path[0] = start; // Par défault tout les noeuds commences par le noeuds de départ
        tab[i].path_length = 1; // La mémoire attribuer du tableau 1 par défault
    }
    
    int indexCurrent = getIndex(tab,start,length); // Récupère l'index dans le tableau du noeud de départ
    tab[indexCurrent].nametag = 0; // Et lui affiche comme étiquette 0 car c'est le départ

    node_t *ptr = NULL; // Pointeur pour voyager dans les noeuds sortants
    while (!isPainted(tab,length)) {
        // Je peint le noeuds que je visite
        tab[indexCurrent].painted = true; // Peint le noeud de départ

        // Je regarde ces noeuds sortants
        ptr = tab[indexCurrent].begin; // Initialise un pointeur sur la liste d'adjacence
        int indexTarget = 0;
        while (ptr) {  // Itère à travers les noeuds voisins
            indexTarget = getIndex(tab,ptr->data,length); // Récupère l'index de la cible dans le tableau à chaque nouveau noeuds voisins
            // Je note les nouveaux chemins que j'ai découvert pour ces noeuds sortant si ce sont les plus courts trouvées 
            if (ptr->weight + tab[indexCurrent].nametag < tab[indexTarget].nametag || tab[indexTarget].nametag == -1 ) { 
                // Si le chemin trouvée est plus court que l'ancien alors
                tab[indexTarget].nametag = ptr->weight + tab[indexCurrent].nametag; // Le nouveau chemin pour le noeud est changée
                concatene_path(tab, indexCurrent, indexTarget); // Sauvegarde le nouveau chemin pour atteindre le noeud
                
            }
            
            ptr = ptr->next;
        }

        // Je parcours mes noeuds à la recherche d'un noeud qui n'a pas était peint et avec l'étiquette la plus faible
        indexCurrent = searchCurrent(tab,length);

    }// Et je répète l'opération


    printf("\n\nApplication algorithme de Djikstra : ");
    for (int i = 0; i < length ; ++i) { // J'affiche mes résultats
        printf("\n\nLe noeud %d : \n    étiquette : %d",tab[i].data,tab[i].nametag);
        printf("\n    Chemin : ");
        for (int j = 0 ; j < tab[i].path_length ; ++j) {
            printf("%d",tab[i].path[j]);
            if ( j + 1 != tab[i].path_length ) printf("->");
        }
    }
    
    return;
}

/*----------------------- Parcour en largeur  -----------------------*/

/*! @brief Réalise un parcour en largeur sur le graphe
 *  @param g Le graphe à analyser
 *  @param start le noeud de départ dans le graphe
 * 
 * Comportement : 
 * Initialise un tableau de noeud de Djikstra j'ai conservé cette structure car il était possible de garder
 * la même approche de résolution étant donnée que les deux algorithmes sont assez similaires.
 * Ensuite commence initialise le tableau de traitement qui est une queue représentant l'ordre dans lequelle on
 * va traité les noeuds. Puis tant qu'on à pas exploré tout le graphe on réalise l'algorithme.
 * i. e.  On regarde les noeuds sortants du noeuds que l'on traite si ces derniers n'ont pas était exploré.
 * On leur donne comme nouvelle étiquette celle du noeud actuellement traité + 1 et on rajoute au chemin du noeud
 * actuellement traité la valeur du nouveau noeud pour l'affecté au nouveau noeud. Ensuite on peint le noeud que l'on explore.
 * Et on ajoute le noeud explore à la queue de noeud à traité. Puis on passe au noeud à traité suivant.
 * Et à la toute fin on affiche les informations récupérés.
 */
void parcour_largeur(graph_t *g, int start) {
    node_d_t *tab = malloc(g->memory_allocated * sizeof(node_d_t)); // Alloue un tableau de la taille du nombre de noeuds
    int length = g->memory_allocated ; //
    // Initialise un tableau de noeuds de djisktra de même taille que le nombre
    // de sommets du graphe

    for (int i = 0; i < length ; ++i) { // Initialise le tableau de noeuds de djikstra
        tab[i].data = g->tab[i].data; // Récupère le nom de chaque sommets du graphe
        tab[i].painted = false; // Par défault les noeuds n'ont pas était vue
        tab[i].nametag = -1; // Par défault le poid pour y accéder est infini ici représenter par -1
        tab[i].begin = g->tab[i].begin; // Associe les noeuds voisins au nouveau tableau

        tab[i].path = malloc(g->memory_allocated * sizeof(int)); // Alloue un tableau de la taille maximale que le chemin peux prendre
        tab[i].path[0] = start; // Par défault tout les noeuds commences par le noeuds de départ
        tab[i].path_length = 1; // La mémoire attribuer du tableau 1 par défault
    }


    node_t *ptr = NULL; // Pointeur pour voyager dans les noeuds sortants

    int *treatement_tab = malloc(length * sizeof(int)); // Initialise la liste des noeuds à traités
    tab[getIndex(tab,start,length)].nametag = 0; // Récupère l'index du premier noeud et lui affiche comme étiquette 0
    treatement_tab[0] = getIndex(tab,start,length); // Affecte le premier noeud comme départ à traité
    tab[treatement_tab[0]].painted = true; // Et je peint le noeud de départ

    int indexCurrent = 0; // Comment le traitement du tableau a partir du départ
    int tab_length = 1; // Taille de la liste à traité initialement 1

    while (!isPainted(tab,length)) {// Tant que tout les noeuds ne sont pas peints
        // J'ai une liste de noeuds auquels je vais regardé les noeuds sortant au départ le start
        ptr = tab[treatement_tab[indexCurrent]].begin;
    
        while (ptr) { // Je regarde ces noeuds sortants
            // Je les rajoutes comme distancé de étiquette + 1 si ils n'ont pas était exploré
            if (!tab[getIndex(tab,ptr->data,length)].painted) {
                tab[getIndex(tab,ptr->data,length)].nametag = tab[treatement_tab[indexCurrent]].nametag + 1; // Etiquette + 1 
                tab[getIndex(tab,ptr->data,length)].painted = true; // On peint le noeud maintenant qu'il est vue
                concatene_path(tab, treatement_tab[indexCurrent], getIndex(tab, ptr->data, length) ); // Sauvegarde le nouveau chemin pour atteindre le noeud
                
                treatement_tab[tab_length] = getIndex(tab,ptr->data,length); // Ajoute le noeud dans la liste à traité
                tab_length += 1; // Agrandi la liste à traité de 1
            }
            ptr = ptr->next;
        }

        indexCurrent += 1; // Passe à l'élément suivant à traité

    }// Et je répète

    printf("\n\nApplication Parcour en largeur : ");
    for (int i = 0; i < length ; ++i) { // J'affiche mes résultats
        printf("\n\nLe noeud %d : \n    étiquette : %d",tab[i].data,tab[i].nametag); 
        // Affiche le noeud et le pour l'atteindre
        printf("\n    Chemin : "); // Affiche le chemin
        for (int j = 0 ; j < tab[i].path_length ; ++j) {
            printf("%d",tab[i].path[j]);
            if ( j + 1 != tab[i].path_length ) printf("->");
        }
    }

    return;
}

/*----------------------- Parcour en profondeur  -----------------------*/


