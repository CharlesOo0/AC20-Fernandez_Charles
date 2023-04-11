#ifndef _ARBRE_H_
#define _ARBRE_H_

 /* Définition d'un booléen */

 typedef enum { false, true } bool;

 /* Définition d'un arbre */

 typedef struct _arbre{
    struct _arbre* Agauche;
    struct _arbre* Adroite;
    int data;
 }arbre_t;

 /* Prototypes arbre */

 void erase_tree(arbre_t *tree);
 arbre_t *create_tree(int data);
 void display_tree_preorder(arbre_t *root);
 void display_tree_inorder(arbre_t *root);
 void display_tree_postorder(arbre_t *root);
 void add_tree(arbre_t *root, int target, int data, int leftOrRight);
 arbre_t *tree_maker(int nodes[], size_t lengthNodes);
 int node_counting(arbre_t *root);
 int get_parent(arbre_t *root, int target, int parent);
 bool is_node(arbre_t *root, int target);
 
#endif
