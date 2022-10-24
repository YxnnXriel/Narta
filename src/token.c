#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/token.h"



token init_token(int type , char *value){
    token tok = calloc(1,sizeof(*tok));
    tok->value = strdup(value);
    tok->type = type;
    return tok;
}
char *token_type_as_string(int type){
    switch (type)
    {
        case T_ID: return"T_ID" ;
        case T_INT: return"T_INT" ;
        case T_STRING: return"T_STRING" ;    
        case T_ASTERISK: return"T_ASTERISK" ; // *
        case T_LBRACE: return"T_LBRACE" ; // [
        case T_RBRACE: return"T_RBRACE" ; // ]
        case T_OR: return"T_OR" ;// ||
        case T_AND: return"T_AND" ;// &&
        case T_COMA: return"T_COMA" ; // ,
        case T_INF: return"T_INF" ; // <
        case T_SUP: return"T_SUP" ;// >
        case T_EQUAL: return"T_EQUAL" ;// = 
        case T_SUP_EQUAL: return"T_SUP_EQUAL" ; // >=
        case T_INF_EQUAL: return"T_INF_EQUAL" ; // <=
        case T_DIFF: return"T_DIFF" ; // !=
        case T_LPARENT: return"T_LPARENT" ; // (
        case T_RPARENT: return"T_RPARENT" ; // )
        case T_CHAMP: return "T_CHAMP";
        case T_TIRET : return "T_TIRET";
        case T_EOF: return"T_EOF" ; 
    default: return NULL;
    }
}


int token_convert_to_type(char *s){

    if(strcmp("<",s) == 0 )return T_INF;
    if(strcmp("<=",s) == 0 )return T_INF_EQUAL;
    if(strcmp("=",s) == 0 )return T_EQUAL;
    if(strcmp(">",s) == 0 )return T_SUP;
    if(strcmp(">=",s) == 0 )return T_SUP_EQUAL;
    if(strcmp("!=",s) == 0 )return T_DIFF;

    return -1;
}