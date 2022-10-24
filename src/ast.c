#include <stdio.h>
#include <stdlib.h>
#include "include/ast.h"


ast init_ast(int type){
    ast ast = calloc(1,sizeof(*ast));



    ast->type = type;
    ast->list_op = (void *)0;
    ast->list_op_size = 0;
    
    ast->list_champ = ListString();
    ast->list_enter = ListString();
    ast->list_enter_type = (void*)0;

    ast->list_champ_condition = ListString();

    /** AST SELECT **/
    ast->is_all = 0; // pour savoir si c'est toute la valeur a retourner
    ast->is_all_select = 0;


    /** AST INSERT **/
    ast->list_insert_value = (void*)0;
    ast->list_insert_value_size = 0;

    /** AST UPDATE **/
    ast->list_champ_new_value = ListString();

    ast->coumpoud = (void*)0;
    ast->coumpoud_size = 0;
    return ast;
}