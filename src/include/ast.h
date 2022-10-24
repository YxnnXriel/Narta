#ifndef __AST_H__
#define __AST_H__

#include "str.h"

typedef struct AST_STRUCT
{
    enum{
        AST_SELECT,
        AST_COUPOUND,
        AST_UPDATE,
        AST_DELETE,
        AST_CREATE,
        AST_INSERT,
        AST_PRINT,
        AST_NOOP,
    }type;


    int *list_op;
    size_t list_op_size;
    
    listString list_champ_condition;
    listString list_champ;
    listString list_enter;
    int *list_enter_type;


    /** AST SELECT **/
    int is_all; // pour savoir si c'est toute la valeur a retourner
    int is_all_select;

    /** AST INSERT **/
    listString_t **list_insert_value;
    int list_insert_value_size;
    /** AST UPDATE **/
    listString list_champ_new_value;

    struct AST_STRUCT **coumpoud;
    int coumpoud_size;
}ast_t,*ast;

ast init_ast(int type);




#endif