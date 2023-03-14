#include "liste_v2.c"

int main() {

    liste_propriete_t *une_liste_propriete = malloc(sizeof(liste_propriete_t));
    une_liste_propriete->list_length = 0;
    une_liste_propriete->head = NULL;
    une_liste_propriete->tail = NULL;

    // Test le display
    display_list_v2(une_liste_propriete);

    // Test le add head
    une_liste_propriete->head = add_head_list_v2(une_liste_propriete, 5);
    une_liste_propriete->head = add_head_list_v2(une_liste_propriete, 2);
    une_liste_propriete->head = add_head_list_v2(une_liste_propriete, 7);

    display_list_v2(une_liste_propriete);

    // Test le add tail
    une_liste_propriete->head = add_tail_list_v2(une_liste_propriete, 1);
    une_liste_propriete->head = add_tail_list_v2(une_liste_propriete, 9);
    une_liste_propriete->head = add_tail_list_v2(une_liste_propriete, 3);

    display_list_v2(une_liste_propriete);

    // Test le erase list
    erase_list_v2(une_liste_propriete);

    display_list_v2(une_liste_propriete);

    for (int i=0; i<10; ++i)
        une_liste_propriete->head = add_tail_list_v2(une_liste_propriete, i+1);

    // Test le delete head
    une_liste_propriete->head = delete_head_list_v2(une_liste_propriete);
    une_liste_propriete->head = delete_head_list_v2(une_liste_propriete);
    une_liste_propriete->head = delete_head_list_v2(une_liste_propriete);

    display_list_v2(une_liste_propriete);

    // Test le delete tail
    
    une_liste_propriete->head = delete_tail_list_v2(une_liste_propriete);
    une_liste_propriete->head = delete_tail_list_v2(une_liste_propriete);
    une_liste_propriete->head = delete_tail_list_v2(une_liste_propriete);

    display_list_v2(une_liste_propriete);

    erase_list_v2(une_liste_propriete);
    

    // Test cas d'application Multiply two list
    
    liste_propriete_t *headFirstList = malloc(sizeof(liste_propriete_t));
    headFirstList->list_length = 0;
    headFirstList->head = NULL;
    headFirstList->tail = NULL;

    headFirstList->head = add_head_list_v2(headFirstList, 5);
    headFirstList->head = add_head_list_v2(headFirstList, 2);
    headFirstList->head = add_head_list_v2(headFirstList, 7);
    

    liste_propriete_t *deux_liste_propriete = malloc(sizeof(liste_propriete_t));
    deux_liste_propriete->list_length = 0;
    deux_liste_propriete->head = NULL;
    deux_liste_propriete->tail = deux_liste_propriete->head;

    deux_liste_propriete->head = add_tail_list_v2(deux_liste_propriete, 1);
    deux_liste_propriete->head = add_tail_list_v2(deux_liste_propriete, 9);
    deux_liste_propriete->head = add_tail_list_v2(deux_liste_propriete, 3);
    

    headFirstList = multiply_twolist_v2(headFirstList,deux_liste_propriete);

    display_list_v2(headFirstList);
    

    return EXIT_SUCCESS;
}
