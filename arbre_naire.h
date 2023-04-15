#ifndef _ARBRE_NAIRE_H_
#define _ARBRE_NAIRE_H_

 /* Définition d'un booléen */

 typedef enum { false, true } bool;

/* Définition d'un arbre n-aire */
typedef struct _narbre {
    int data;
    struct _narbre *sibling;
    struct _narbre *child; 
}narbre_t;

 /* Prototypes */

narbre_t *create_ntree(int data);
void erase_ntree(narbre_t *root);

void display_ntree(narbre_t* root, int level);

narbre_t* find_node(narbre_t* root, int target);
narbre_t* find_parent(narbre_t* root, int target, narbre_t* parent);

void add_sibling(narbre_t* root, int target, int data);
void add_child(narbre_t* root, int parent_data, int child_data);
void delete_node(narbre_t *root, int target);

int node_counting(narbre_t* root);
bool is_node(narbre_t* root, int target);
int get_level(narbre_t* root, int target, int level);

void print_path(narbre_t *root, int target);

#endif
