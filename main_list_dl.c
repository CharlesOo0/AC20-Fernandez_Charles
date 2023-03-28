#include <stdio.h>
#include <stdlib.h>

#include "double_liste.c"

void main(){
    liste_double_t *une_liste = NULL;

    display_list_dl(une_liste);

    une_liste = add_head_dl(une_liste,5);
    une_liste = add_head_dl(une_liste,5);
    une_liste = add_head_dl(une_liste,5);
    
    display_list_dl(une_liste);

    
    liste_double_t *deux_liste = NULL;

    display_list_dl(deux_liste);

    deux_liste = add_tail_list_dl(deux_liste,8);
    deux_liste = add_tail_list_dl(deux_liste,8);
    deux_liste = add_tail_list_dl(deux_liste,7);

    display_list_dl(deux_liste);

    deux_liste = delete_head_list_dl(deux_liste);
    deux_liste = delete_head_list_dl(deux_liste);
    deux_liste = delete_head_list_dl(deux_liste);
    deux_liste = delete_head_list_dl(deux_liste);

    display_list_dl(deux_liste);

    une_liste = delete_tail_list_dl(une_liste);
    une_liste = delete_tail_list_dl(une_liste);
    une_liste = delete_tail_list_dl(une_liste);
    une_liste = delete_tail_list_dl(une_liste);

    display_list_dl(une_liste);

    une_liste = add_head_dl(une_liste,5);
    une_liste = add_head_dl(une_liste,5);
    une_liste = add_head_dl(une_liste,5);
    
    display_list_dl(une_liste);

    erase_list_dl(une_liste);

    une_liste = NULL;

    display_list_dl(une_liste);

    // Test le add target

    printf("Test du add target ici --> \n");

    une_liste = add_head_dl(une_liste,10);
    une_liste = add_head_dl(une_liste,7);
    une_liste = add_head_dl(une_liste,2);

    display_list_dl(une_liste);

    une_liste = add_target_dl(une_liste,185,0);

    display_list_dl(une_liste);

    // Test le delete target 

    printf("Test du add target ici --> \n");

    display_list_dl(une_liste);

    une_liste = delete_targert_dl(une_liste,2);

    display_list_dl(une_liste);
    
}
