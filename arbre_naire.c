#include "arbre_naire.h"


/*! @brief Initialise un noeud pour un arbre n-aire
 *  @param data entier représentant la donnée du noeud
 *
 * Comportement :
 * Initialise le noeud dans la mémoire, lui affecte la donnée en argument.
 * Par défault le noeud n'a pas de noeud fils et de père. Retourne le noeud.
 */
narbre_t *create_ntree(int data) {
    narbre_t *new_tree = malloc(sizeof(narbre_t)); // Initialise l'arbre dans la mémoire
    new_tree->data = data; // Lui affecte la data en argument
    new_tree->sibling = NULL; // Pas de frere
    new_tree->child = NULL; // Pas d'enfant

    return new_tree;
}

/*! @brief Efface récursivement un arbre n-aire
 *  @param root Un pointeur vers la tête de l'arbre
 *
 * Comportement :
 * A la manière du display_ntree(). Première nous allons regarder si le noeud en argument
 * est NULL. Si c'est le cas la fonction s'arrête. Sinon on fait un appel récursif sur le noeud fils
 * de notre noeud. Qui lui même fait un appel jusqu'au noeud fils le plus bas et non NULL. Une fois ce dernier atteint
 * on explore tout ces freres une fois le dernier frere atteint on remonte tout les noeuds en les libérant. Et on fait
 * cette opération pour les noeuds freres des noeuds fils.
 */
void erase_ntree(narbre_t *root) {
    if (root) { // Si le noeud n'est pas NULL
        erase_ntree(root->child); // On par dans les noeuds fils
        erase_ntree(root->sibling); // On par dans les noeuds frères
        free(root); // On libère après avoir regarder tout ces noeuds fils et frère le noeud
    }
}

 /*! @brief Affiche un arbre n-aire
  *  @param root Un pointeur vers la tête de l'arbre
  *  @param level Le niveau de l'arbre dans lequel on ce situe
  * 
  * Comportement :
  * Dans un premier temp la fonction regarde si le noeud en racine est NULL ou non.
  * Si il est NULL le programme s'arrête sinon on parcour le noeud récursivement.
  * Première on affiche la valeur du noeud avec un indentation pour spécified son niveau.
  * D'ou le level*4. Ensuite on parcours son noeud fils. Et une fois que le noeud fils.
  * A parcouru récursivement ces noeuds fils puis leur frêre on parcours ces frêres.
  */
void display_ntree(narbre_t* root, int level) {
    if (root) { // Si le noeud n'est pas NULL
        printf("%*s%d\n", level * 4, "", root->data); // Affiche la valeur du noeud présent
        // Avec une indentation (%*s,level * 4)

        display_ntree(root->child, level + 1); // On par dans les noeuds fils on augmentant
        // le niveau de 1, donc la taille de l'indentation.

        display_ntree(root->sibling, level); // On par vers les frêres du noeud actuelle
        // sans changer l'indentation
    }
}

/*! @brief Cherche un noeud dans l'arbre et le renvoie si il existe
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target_data La valeur de l'étiquette de la cible
 * 
 * Comportement :
 * Parcours récursivement l'arbre un peu à la manière de display_ntree().
 * Premièrement on regarde si le noeud en argument est NULL si c'est le cas
 * on retourne NULL car on à pas trouver la cible. Ensuite on vérifie que le noeud
 * actuelle est la cible, si c'est le cas on le retourne. Si aucun de ces deux cas
 * ne ce présente on va parcourir récursivement les fils les plus profonds du noeuds.
 * Pour chercher la cible, puis remonter récursivement toujours à la recherche de la cible.
 * Si on rencontre la cible on retourne le noeud. Pour bypass le fait que quand on ne rencontre pas la cible
 * mais plutot la fin de l'arbre, on vérifie à chaque appel de fonction le return qu'on obtient,
 * si ce dernier est différent de NULL alors on à trouver la cible.
 */
narbre_t* find_node(narbre_t* root, int target) {
    if (!root) { // Si le noeud est NULL retourne NULL
        return NULL;
    } else if (root->data == target) { // Si le noeud est la cible retourne le noeud
        return root;
    } else { // Sinon parcour récursivement l'arbre
        narbre_t* target_node = find_node(root->child, target); // Appel récursif vers les fils
        if (target_node) { // Si c'est la cible il est différent de NULL
            return target_node; // Donc le retourne 
        } else { // Sinon on va regarder les freres
            return find_node(root->sibling, target); // Appel récursif vers les freres
        }
    }
}




/*! @brief Ajoute un noeud frère a un noeud
 *  @param root Un pointeur vers la tête 
 *  @param target La valeur de l'étiquette de la cible
 *  @param data La valeur de l'étiquette du nouveau noeud
 *  
 * Comportement :
 * Utilise la fonction find_node() pour trouver le noeud cible.
 * Ensuite crée notre nouveau noeud si on trouve le noeud cible.
 * Puis ajoute ce dernier à la fin de la liste chaînée de noeud frère.
 */
void add_sibling(narbre_t* root, int target, int data) {

    narbre_t* target_node = find_node(root, target); // Utilise find_node() pour chercher le noeud cible
    if (!target_node) {  // Si on ne le trouve pas alors message d'erreur
        printf("\nErreur noeud introuvable");
        return;
    }

    // Si on trouve la cible, on initialise notre nouveau noeud frere
    narbre_t *new_node = create_ntree(data);

    // A la manière des listes chaînée on va à la fin de la liste
    // chainée de notre noeud cible
    while (target_node->sibling) { // Tant que frère suivant non NULL
        target_node = target_node->sibling; // On passe au frère suivant
    }

    target_node->sibling = new_node; // Ajoute le nouveau noeud frère
}

/*! @brief Ajoute un noeud fils a un noeud
 *  @param root Un pointeur vers la tête 
 *  @param target La valeur de l'étiquette de la cible
 *  @param data La valeur de l'étiquette du nouveau noeud
 * 
 * Comportement :
 * Utilise find_node() pour trouver le noeud cible dans l'arbre.
 * Si on trouve le noeud cible on initialise notre nouveau noeud avec la data.
 * Et on l'ajoute en tête des noeuds fils du noeud cible.
 */
void add_child(narbre_t* root, int target, int data) {
    narbre_t* target_node = find_node(root, target); // Utilise find_node() pour chercher le noeud cible
    if (!target_node) {  // Si on ne le trouve pas alors message d'erreur
        printf("\nErreur noeud introuvable");
        return;
    }

    // Si on trouve la cible, on initialise notre nouveau noeud fils
    narbre_t *new_node = create_ntree(data);

    // Fait un add_head à la manière des listes chaînées
    new_node->sibling = target_node->child; // Les noeuds frères du nouveau noeud son les
    // noeuds fils du parent
    target_node->child = new_node; // Le nouveau début des noeuds fils est le nouveau noeud
}

/*! @brief Compte le nombre de noeud dans un arbre n-aire
 *  @param root un pointeur vers la tête de l'arbre
 *
 * Comportement :
 * Vérifie si le noeud est NULL si oui retourne 0. Sinon intialise un
 * compteur à 1 car le noeud actuelle n'est pas NULL. Puis mémorise le premier fils du noeud.
 * Tant que ce dernier n'est pas NULL, on ajoute à count un appelle récursif sur notre fonction
 * avec comme paramère le premier fils. Cette appel va nous permettre d'aller au premier fils de chaque noeud.
 * Donc de parcourir tout les étage. Puis affecte au fils son frère. Et boucle jusqu'au dernier frère afin
 * de parcourir tout les noeuds d'un étage. Mais aussi tout les étages de chaque noeud indirectement.
 * Pour finir retourne count.
 */
int node_counting(narbre_t* root) {
    if (!root) { // Si le noeud est NULL on dans une extrémité de l'arbre
        return 0; // retourne 0
    }
    int count = 1;  // Compte les noeuds, 1 car on compte la node actuelle
    narbre_t* child = root->child;
    while (child) { // Ce while permet d'itérer dans chaque noeud d'un étage
        count += node_counting(child);  // Appel récursif pour aller au fils du fils
        // permet donc de descendre d'étage en étage
        child = child->sibling; // Passe de noeud en noeud dans l'étage
    }
    return count; // Retourne ce que l'on à compter
}

/*! @brief Vérifie la présence d'un noeud dans l'arbre
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target La valeur de la cible
 * 
 * Comportement :
 * Dans un premier temps vérifie si le noeud est NULL si oui,
 * retourne false car cela ne peux donc pas être la cible.
 * Si le noeud est la cible alors retourne true.
 * Si le noeud n'est pas NULL mais n'est pas la cible.
 * Alors parcours récursivement les fils et frères du noeud.
 * Et permet de prioriser le true dans la somme de booléen avec ||.
 */
bool is_node(narbre_t* root, int target) {
    if (!root) { // Si la racine est NULL ce n'est pas la cible
        return false; // donc retourne false
    }
    else if (root->data == target) { // Si la racine est la cible
        return true; // retourne true
    }
    else { // Si le noeud n'est pas la cible
        return is_node(root->child, target) || is_node(root->sibling, target);
        // Parcours ces noeuds fils et frère récursivement
    }
}

/*! @brief Retourne le parent d'un noeud
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target La valeur entière de la cible
 *  @param parent Le parent du noeud root, NULL au première appelle
 * 
 * Comportement :
 * A la mnière du find_node() va parcourir l'arbre récursivement. Dans un premier temp
 * on regarde si le noeud en argument est NULL si ce dernier l'est on retourne NULL.
 * Si ce dernier n'est pas NULL et est le noeud cible alors on retourne son parent
 * qui à était envoyé en paramètre. Si ce dernier n'est pas la cible alors on parcours 
 * récursivement tout ces fils. Puis on regarde si ces dernier son la cible en regardant ce
 * que retourne l'appel de fonction != NULL si il trouve la cible. Si il ne trouve pas la cible
 * dans le fils de chaque noeud on parcours récursivement ces frères et leur fils et ainsi dessuite.
 */
narbre_t* find_parent(narbre_t* root, int target, narbre_t* parent) {
    if (!root) { // Si le noeud est NULL retourne NULL
        return NULL;
    } else if (root->data == target) { // Si le noeud est la cible retourne le noeud
        return parent;
    } else { // Sinon parcour récursivement l'arbre
        narbre_t* target_node = find_parent(root->child, target, root); // Appel récursif vers les fils
        if (target_node) { // Si c'est la cible il est différent de NULL
            return target_node; // Donc le retourne 
        } else { // Sinon on va regarder les freres
            return find_parent(root->sibling, target, parent); // Appel récursif vers les freres
        }
    }
}

/*! @brief Permet d'effacer un noeud et ces fils
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target La valeur de l'étiquette de la cible
 * 
 * Comportement : 
 * Dans un premier temp on vérifie que la cible est présente dans l'arbre.
 * Si elle n'est pas présente on retourne une erreur.
 * Si elle présente on cherche son parent.
 * Si ce parent est NULL alors la cible est la racine donc on l'efface et on prévient
 * l'utilisateur qu'il à effacer l'arbre.
 * Si le noeud n'est pas la racine on itère dans les fils du noeud jusqu'au fils avant le fils cible.
 * Si le fils cible est le premier fils alors on le decoupe de l'arbre et l'efface.
 * Sinon itère jusqu'à l'élément avant. Puis on découpe le fils de l'arbre et on l'efface.
 */
void delete_node(narbre_t *root, int target) {

    if (!find_node(root,target)) { // Vérifie avec find_node que le noeud
        printf("\nErreur noeud introuvable"); // est présent dans l'arbre
        return; // Si non retourne une erreur
    }

    narbre_t *target_node = find_parent(root,target,NULL); // Cherche le parent du noeud
    if (!target_node){ // Si le parent est NULL
        erase_ntree(root); // Alors on veux effacer la racine
        printf("\nVous avez effacez la racine attention !"); // On prévient l'utilisateur
        return;
    }

    narbre_t *ptr = target_node->child; // Pointeur sur la liste de fils dans laquelle
    // le noeud cible est présent

    if (ptr->data == target) { // Si le premier fils est la cible
        target_node->child = ptr->sibling; // Le parent pointe vers le frere de la cible
        ptr->sibling = NULL; // Le frère de la cible pointe vers NULL
        // On découpe enfaite la cible de l'arbre
        erase_ntree(ptr); // Et on efface la cible
        return; // Met fin au programme
    }

    while (ptr->sibling && ptr->sibling->data != target) { // Itère jusqu'à l'élément avant la cible
        ptr = ptr->sibling; // Vérifie qu'on va pas dans le vide pour la forme
    }

    // Comme avant on va découper la cible de l'arbre
    narbre_t *tmp = ptr->sibling; // On mémorise la cible
    ptr->sibling = tmp->sibling; // Le frère de la cible devient le frère
    // du noeud d'avant
    tmp->sibling = NULL; // La cible ne pointe plus vers son frère
    erase_ntree(tmp); // Efface la cible

}


/*! @brief Permet de connaître le niveau d'un noeud
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target La valeur de l'étiquette de la cible
 *  @param level 0 au début, mais valeur qu'on transmet de fonction en fonction
 * 
 * Comportement :
 * Dans un premier on vérifie si le noeud est NULL. Si oui
 * on retourne -1. Sinon on vérifie qu'il est la cible.
 * Si il est la cible on retourne le niveau dans lequelle on ce situe.
 * Sinon on fait un appelle récursif avec comme argument le fils du noeud
 * et on prend bien soin d'incrémenté le niveau de 1 car on change d'étage.
 * Si le fils trouve le noeud alors ca valeur est différente de -1 donc on le retourne.
 * Car level = {0,1,2,...}. Sinon on fait un appell récursif vers les frères du fils.
 * Sans changer le niveau ce coup-ci car on reste sur le même étage.
 */
int get_level(narbre_t* root, int target, int level) {
    if (!root) { // Si le noeud est NULL retourne -1
        return -1; // pour signifer qu'on à pas trouver la cible
    } else if (root->data == target) { // Si le noeud est la cible retourne le niveau
        return level;
    } else { // Si on n'a pas trouver la cible mais que le noeud existe
        int child_level = get_level(root->child, target, level+1); // On parcours ces fils
        if (child_level != -1) { // Si on à une valeur différent de -1 on a
            return child_level; // trouver la cible alors on retourne child_level
        } else { // Sinon on on cherche des les frères et leur fils
            return get_level(root->sibling, target, level);
        } // Comme les frères sont sur le même étage on ne change pas de niveau
    }
}

/*! @brief Affiche le chemin pour accéder à un noeud
 *  @param root Un pointeur vers la tête de l'arbre
 *  @param target La valeur de l'étiquette de la cible
 * 
 * Comportement :
 * Vérifie si le noeud est dans l'arbre si il ne l'est pas,
 * retourne un message d'erreur. Si il y est crée un tableau
 * d'entier qui va avoir la taille du chemin. Initialise un index 
 * sur le taille max du tableau car on va récupéré le chemin à l'enver.
 * Ensuite on part du noeud cible et tant que le parent est non NULL on passe
 * au parent suivant. On affecte chaque noeud à reculons dans le tableau en
 * décrémentant à chaque itération l'index de 1. Ensuite on affiche le tableau
 * à l'endroit avec une boucle.
 */
void print_path(narbre_t *root, int target) {
    if (!is_node(root,target)) { // Vérifie que le noeud est dans l'arbre
        printf("\nErreur noeud introuvable"); // Message d'erreur
        return;
    }

    int path[get_level(root,target,0)+1]; // Tableau de la taille du chemin
    // qui est égale à la profondeur du noeud plus 1
    int cpt = get_level(root,target,0);  // On initialise un index sur cette
    // taille pour afficher les noeuds dans l'order

    narbre_t *parent = find_node(root,target); // Récupère le noeud
    while (parent) { // Tant que il y à parent on :
        path[cpt] = parent->data; // Affecte à reculons les noeuds
        --cpt; // Affecte à reculons
        parent = find_parent(root,parent->data,NULL); // Récupère le noeud parent du noeud actuelle
    }

    printf("Le chemin : "); // Affiche le chemin dans l'ordre ce coup-ci
    for (int i ; i < get_level(root,target,0)+1 ; ++i) {
        printf("%d ",path[i]);
    }

}
