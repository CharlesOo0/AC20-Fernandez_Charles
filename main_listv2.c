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

    return EXIT_SUCCESS;
}
