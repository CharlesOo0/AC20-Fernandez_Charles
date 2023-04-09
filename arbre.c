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
    if (tree != NULL) {
        arbre_t *tmp = tree; // Memorisé la node
        erase_tree(tree->Agauche); // Va dans l'arbre de gauche de chaque noeud
        erase_tree(tree->Adroite); // Va dans l'arbre de droite de chaque noeud
        free(tmp); // Free l'arbre memorisé
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

/*! @brief Ajoute un élément fils à un noeud précis-*-
 *  @param root Pointeur vers la tête de l'arbre à ajouter
 *  @param data La data du nouvelle élément
 *  @param leftOrRight 0 si ajouter au coté gauche 1 pour le coté droit
 * 
 *  Comportement :
 * - Crée le nouvelle élément lui affecte la data
 * - l'affecte à l'arbre gauche ou droit de l'arbre en argument
 * - selon le choix de l'utilisateur
 */
arbre_t *add_tree(arbre_t *tree, int data, int leftOrRight){
    arbre_t* new_tree = malloc(sizeof(arbre_t)); // Initialise le nouvelle élément
    new_tree->data = data; // Lui affecte la data
    new_tree->Agauche = NULL;
    new_tree->Adroite = NULL;

    if (!tree) {
        return new_tree;
    }

    if (leftOrRight == 0) { // Si l'utilisateur à selectionner gaucher
        tree->Agauche = new_tree; // Alors on l'affecte à gauche
    }else { // Sinon on l'affecte à droite
        tree->Adroite = new_tree;
    }

    return tree;
}

/*! @brief Transforme une liste de noeuds en un arbre binaire complet
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
