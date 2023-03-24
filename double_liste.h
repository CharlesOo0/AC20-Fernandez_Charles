#ifndef _DOUBLE_LISTE_H_
#define _DOUBLE_LISTE_H_

/* Définition liste doublement chainées */

typedef struct _liste_double{
    struct _liste_double* next;
    struct _liste_double* previous;
    int data;
}liste_double_t;

/* Initialisation des prototypes */
void erase_list_dl(liste_double_t* head);
void display_list_dl(liste_double_t* head);
liste_double_t* add_head_dl(liste_double_t* head, int data);
liste_double_t *add_tail_list_dl(liste_double_t* head, int data);
liste_double_t *delete_head_list_dl(liste_double_t* head);
liste_double_t *delete_tail_list_dl(liste_double_t* head);

#endif
