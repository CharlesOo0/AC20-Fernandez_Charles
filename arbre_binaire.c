#include "arbre.h"


/*! @brief Efface un arbre
 *  @param tree Un pointeur vers la racine de l'arbre
 *
 * Comportement :
 * - Part de la racine, parcours récursivement en commencant par les noeuds de gauche
 * - puis les noeuds de droite, et pour finir libère les noeuds dans l'ordre
 * - de parcours
 */
void erase_tree(arbre_t *tree) {
    if (tree) {
        erase_tree(tree->Agauche); // Va dans l'arbre de gauche de chaque noeud
        erase_tree(tree->Adroite); // Va dans l'arbre de droite de chaque noeud
        free(tree); // Free l'arbre
    }
}

/*! @brief Crée une node arbre
 *  @param data Un entier, la data de la nouvelle node
 *
 *  Comportement : 
 * - Initialise un nouvelle élément arbre affecte la data et le retourne
 */
arbre_t *create_tree(int data) {
    arbre_t *new_node = malloc(sizeof(arbre_t)); // Initialise l'arbre
    new_node->data = data; // Lui affecte la data
    new_node->Adroite = NULL; // Pointe vers NULL par défault
    new_node->Agauche = NULL; // pareil

    return new_node;     
}

/*! @brief Affiche un arbre en "pre-order"
 *  @param root Un pointeur vers la racine de l'arbre
 *
 * Comportement :
 * - Traverse récursivement l'arbre en "pre-order"
 * - c'est à dire que nous affichons tout les noeuds en partant
 * - de la racine à gauche puis nous remontons vers le noeud droit une fois
 * - fini tout ceux de gauche et affichons une fois de plus tout ceux de gauche
 * - et ainsi dessuite.
 */
void display_tree_preorder(arbre_t *root) {
    if (root != NULL) {
        printf("%d ",root->data); // Comme on print directement la racine au début
        // Et ensuite l'on va directement à gauche dans l'arbre on comprend
        // que cela affiche les noeuds de gauche en priorité.
        display_tree_preorder(root->Agauche); // Va dans l'arbre de gauche de chaque noeud
        display_tree_preorder(root->Adroite); // Va dans l'arbre de droite de chaque noeud
    }
}

/*! @brief Affiche un arbre en "inorder"
 *  @param root Un pointeur vers la racine de l'arbre
 *
 * Comportement :
 * - Traverse récursivement l'arbre en "inorder"
 * - c'est à dire nous affichons en premier le noeud le plus en
 * - bas a gauche puis son parent puis le fils de droite
 * - puis l'on retourne au parent du parent et on répète le processus
 */
void display_tree_inorder(arbre_t *root) {
    if (root != NULL) { 
        display_tree_inorder(root->Agauche); // Va dans l'arbre de gauche de chaque noeud
        printf("%d ",root->data); // Affiche la valeur une fois le noeud le plus
        // en bas à gauche atteint remonte à son parent car c'est le parent qui permet
        // d'atteindre le noeud en bas et fini par afficher le noeud de droite
        // car on appelle la fonction ci-dessous après
        display_tree_inorder(root->Adroite); // Va dans l'arbre de droite de chaque noeud
    }
}

/*! @brief Affiche un arbre en "post-order"
 *  @param root Un pointeur vers la racine de l'arbre
 *
 * Comportement :
 * - Traverse récursivement l'arbre en "post-order"
 * - c'est à dire nous affichons le noeud parent en dernier
 * - et les noeuds fils en premier en partant de celui de gauche
 */
void display_tree_postorder(arbre_t *root) {
    if (root != NULL) { 
        display_tree_postorder(root->Agauche); // Va dans l'arbre de gauche de chaque noeud
        display_tree_postorder(root->Adroite); // Va dans l'arbre de droite de chaque noeud
        printf("%d ",root->data); // Comme l'affichage du noeud parent ce fait en 
        // dernier on affiche en premier le noeud fils gauche puis fils droit
        // tout en allant evidemment jusqu'au dernier noeud la première fois
    }
}

/*! @brief Compte le nombre de noeud d'un arbre
 *  @param root Un pointeur vers la tête d'un arbre
 *
 * Comportement :
 * - Parcours récursivement l'arbre, à chaque fois que l'on rencontre
 * - un noeud non NULL on retourne 1 (Pour le noeud non NULL présent)
 * - plus un appel récursif à la fonction sur le fils de gauche plus
 * - le fils de droite également. Jusqu'à rencontré des fils NULL.
 * - Une fois ces derniers trouvée retourne 0.
 */
int node_counting(arbre_t *root) {
    if (!root) { // Si on tombe sur un fils NULL alors il n'a pas de sous fils
        return 0; // Et donc on n'ajoute pas 1 au total de noeud car le noeud actuelle
        // n'existe pas
    }else { // Si le noeud sur lequelle on tombe existe on ajoute 1 au total et on va regarder
    // Si ces fils existe
        return 1 + node_counting(root->Agauche) + node_counting(root->Adroite);
    }
}

/*! @brief Cherche la valeur du parent d'un noeud à trouver
 *  @param root Un pointeur vers la tête du noeud à analysé
 *  @param target La valeur du noeud à trouver
 *  @param parent La valeur du parent qui exécute la fonction
 * 
 * Comportement :
 * - Nous partons du principe que chaque noeud de l'arbre sont distinct
 * - et que l'arbre n'a pas de noeud égale à 0. Cette fonction parcours
 * - l'arbre récursivement. Et un peu à la manière du node counting.
 * - Nous allons retournée la somme de toute les exécutions de la fonction.
 * - La fonction retourne quelque chose dans deux cas le premier on rencontre.
 * - Le noeud cible donc on retourne la valeur de sont parent.
 * - Le second on est sur un noeud NULL donc on retourne 0.
 * - Ainsi en incrémentant tout les appelles de fonctions, si il n'y à pas de doublon
 * - on retrouve dans notre return la valeur du parent.
 */
int get_parent(arbre_t *root, int target, int parent) {
    
    if (root) { // Regarde si le noeud en argument est non NULL

        if(root->data == target) { // Si la valeur de ce noeud est égale à la target
            return parent;
            //printf("\nThe parent of %d is %d",target,parent); // Alors retourne le parent envoyé en argument
        }else { // Sinon par exploré les fils de gauche et droite récursivement
            return get_parent(root->Agauche,target,root->data) + get_parent(root->Adroite,target,root->data); // Le parent devient la valeur du noeud exploré     
        }

    } 
    return 0;
}


/*! @brief Ajoute un élément fils à un noeud précis ( Par du principe que chaque noeud est différent )
 *  @param target La valeur du noeud parent
 *  @param data La valeur du nouveau noeud fils
 *  @param leftOrRight L'utilisateur précise à gauche 0 ou à droite 1 du noeud parent
 * 
 * Comportement :
 * - Parcours récursivement l'arbre à la manière des display
 * - Quand il rencontre le noeud cible on y ajoute le noeud fils
 */
void add_tree(arbre_t *tree, int target, int data, int leftOrRight){

    if (tree) {
        if (tree->data == target) { // Si on rencontre le noeud cible

            if (leftOrRight == 0) { // Si 0 on l'ajoute a gauche
                if (tree->Agauche) { // Si il y à déjà une node ici la remplace
                    free(tree->Agauche);
                }
                tree->Agauche = create_tree(data); // Crée le nouveau noeud et l'affecte
            } else{ // Si 1 à droite
                if (tree->Adroite) { // Si il y à déjà une node ici la remplace
                    free(tree->Agauche);
                }
                tree->Adroite = create_tree(data); // Crée le nouveau noeud et l'affecte
            }

            return;
        }

        add_tree(tree->Agauche,target,data,leftOrRight); // Appelle récursif sur la gauche
        add_tree(tree->Adroite,target,data,leftOrRight); // Appelle récusif sur la droite
    }

}

/*! @brief Transforme une liste de noeuds représentant un arbre binaire complet en un arbre binaire complet
 *  @param nodes Une liste de noeuds sous forme d'entier
 *  @param lengthNodes La taille de cette liste de noeud
 *  
 * Comportement :
 * - Vérifie si la liste est vide si oui alors l'arbre est NULL
 * - Ensuite crée une liste d'arbre qui va représenté les parents
 * - Garde en mémoire un index du parent présent et l'index des cases du tableaux occupé par un parent
 * - Itère dans tout le tableau et affecte successivement au parent séléctionner les deux noeuds fils
 * - suivant puis c'est deux noeuds fils les ajoutes à la listes de parent et ainsi desuite.
 */

arbre_t *tree_maker(int nodes[], size_t lengthNodes) {

    if (lengthNodes == 0) { // Si la listes de noeuds est vide alors notre arbre est NULL
        return NULL;
    } // Si ce n'est pas NULL alors il y à au moins un noeud

    arbre_t *tree = malloc(sizeof(arbre_t)); // Initialise notre arbre
    tree = create_tree(nodes[0]); // Le premier noeud est la racine

    arbre_t *parents[lengthNodes]; // Crée notre liste de parents de même taile que la liste

    int tabIndex = 1; // Index pour parcourir le tableau
    int currentParent = 0; // Selectionne le premier parent donc la racine
    int filled = 1; // Nous avons actuellement une case du tableau remplie

    parents[currentParent] = tree; // Le premier parent est la racine

    while (tabIndex < lengthNodes) { // Itère à travers tout les noeuds du tableau

        parents[currentParent]->Agauche = create_tree(nodes[tabIndex]); // Le fils de gauche du parent est 
        // le premier noeuds pas de doute sur son existance car le while s'exécute
        parents[filled] = parents[currentParent]->Agauche; // Ajoute ce noeud à la liste de parent

        ++filled; // Ajoute 1 à la taille des cases occupées dans la listes de parent
        ++tabIndex; // Passe à l'index d'après dans le tableau

        if (tabIndex < lengthNodes) { // Si l'index d'après est toujours dans l'intervalle du tableau
            parents[currentParent]->Adroite = create_tree(nodes[tabIndex]); // Alors le noeud existe
            // Donc l'affecte en tant que fils droit du parent
            parents[filled] = parents[currentParent]->Adroite; // Ajoute ce fils à la liste des parents

            ++filled; // Ajoute 1 à la taille des cases occupées dans la listes de parent
            ++tabIndex; // Passe à l'index d'après dans le tableau
        }

        ++currentParent; // Selectionne le prochain parent
    }

    free(parents); // Free notre liste de parent

    return tree; // Retourne la racine
}

/*! @brief Vérifie si un noeud est présent dans l'arbre
 *  @param root Un pointeur vers la tête de l'arbre 
 *  @param target Un entier représentant la valeur de la cible
 * 
 * Comportement :
 * - Ce balade récursivement dans l'arbre, avec des appels sur les noeuds
 * - gauche et droit jusqu'à ce qu'il soit NULL.
 * - Une fois le NULL trouvée retourne false. Tant qu'ils sont non NULL
 * - on vérifie si on à trouver la cible si oui retourne true. Sinon retourne
 * - les appelles récursif aux fils avec un ||.
 * - Si on à un seul true dans tout le retour cela comptera comme un true.
 * - A cause du || .
 */
bool is_node(arbre_t *root, int target) {

    if (root) { // Si le noeud n'est pas NULL
        if (root->data == target) { // Si on trouve la cible
            return true; // Retourne true
        }

        return is_node(root->Agauche,target) || is_node(root->Adroite,target); // Sinon retourne 
    }   // les appelles récursif gauche et droite avec || car si on rencontre un seul true
    // Cela retournera true

    return false; // Si le noeud est NULL retourne false
}
