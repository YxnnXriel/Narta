#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/parser.h"
#include <string.h>

parser init_parser(lexer lex){
    parser pars = calloc(1,sizeof(*pars));
    pars->lex = lex;
    pars->prev_token = (void*)0;
    pars->current_token = GetNextToken(pars->lex);

    return pars;
}


static int is_an_op(int type){
    switch (type)
    {
        case T_SUP: return type; break;
        case T_SUP_EQUAL: return type; break;
        case T_INF: return type; break;
        case T_INF_EQUAL: return type; break;
        case T_DIFF: return type; break;
        case T_EQUAL: return type; break;


        default: return -1;break;
    }
}

int parser_verif_syntaxe(parser pars,char *cmd){
    if(strcmp(cmd,pars->current_token->value)!=0){
        printf("Erreur, key attendu : `%s` , actu : `%s` \n",pars->current_token->value,cmd);
        exit(1);
    }
    return 1;
}

void parser_eat(parser pars, int type){

    if(pars->current_token->type == type){
        // if(pars->prev_token != (void*)0)
        //     free(pars->prev_token);
        
        pars->prev_token = pars->current_token; 
        pars->current_token = GetNextToken(pars->lex);
    }else{
        printf("Erreur de syntaxe , `%s` attendu , actuellement %s ",
            token_type_as_string(type),
            token_type_as_string(pars->current_token->type)
        );
    }

}

ast parser_parse(parser pars){
    return parser_parse_statements(pars);
}

ast parser_parse_statements(parser pars){
    
    ast coup_master = init_ast(AST_COUPOUND);

    coup_master->coumpoud = calloc(1,sizeof(*coup_master->coumpoud));


    ast state = parser_parse_statement(pars);

    coup_master->coumpoud[0] = state;

    coup_master->coumpoud_size += 1;

    while (pars->current_token->type == T_SEMI)
    {
        parser_eat(pars,T_SEMI);
        ast state = parser_parse_statement(pars);
        coup_master->coumpoud_size += 1;
        
        coup_master->coumpoud = realloc(coup_master->coumpoud,
        coup_master->coumpoud_size
         * sizeof(*coup_master->coumpoud));
        
        coup_master->coumpoud[coup_master->coumpoud_size -1] = state;
        
    }
    

    return coup_master;
}

ast parser_parse_statement(parser pars){
    switch (pars->current_token->type)
    {
        case T_ID: return parser_parse_token_id(pars); break;
    
    default:
        break;
    }
    return init_ast(AST_NOOP);

}


ast parser_parse_token_id(parser pars){

    if(strcmp("select",pars->current_token->value)==0){
        return parser_parse_select(pars);
    }
    if(strcmp("insert",pars->current_token->value)==0){
        return parser_parse_insert(pars);
    }
    if(strcmp("update",pars->current_token->value)==0){
        return parser_parse_update(pars);
    }
    if(strcmp("delete",pars->current_token->value)==0){
        return parser_parse_delete(pars);
    }
    if(strcmp("create",pars->current_token->value)==0){
        return parser_parse_create_table(pars);
    }

    if(strcmp("print",pars->current_token->value)==0){
        return parser_parse_print(pars);
    }
    return init_ast(AST_NOOP);
}
ast parser_parse_select(parser pars){
    ast Select = init_ast(AST_SELECT);
    // SELECT
    parser_eat(pars,T_ID);
    if(pars->current_token->type == T_ASTERISK){
        // *
        parser_eat(pars,T_ASTERISK);
        Select->is_all = true;
        ListString_Append_Item_Str(Select->list_champ,"all");
    }else if(pars->current_token->type == T_LPARENT){
        // (
        Select->is_all = false;

            parser_eat(pars,T_LPARENT);
            while (pars->current_token->type != T_RPARENT){
                switch (pars->current_token->type){
                    case T_CHAMP:{
                        char *s = strdup(pars->current_token->value);
                        ListString_Append_Item_Str(Select->list_champ,s);

                        parser_eat(pars,T_CHAMP);
                    }break;

                    case T_ID:{
                        char *s = strdup(pars->current_token->value);
                        ListString_Append_Item_Str(Select->list_champ,s);
                        parser_eat(pars,T_ID);
                    }break;
                    default:break;
                }

                if(pars->current_token->type == T_COMA)
                    parser_eat(pars,T_COMA);
            }
            parser_eat(pars,T_RPARENT);
        // )
    }else if (pars->current_token->type == T_ID){
        Select->is_all = false;
        while (strcmp(pars->current_token->value,"from") != 0)
        {
            char *s = strdup(pars->current_token->value);
            ListString_Append_Item_Str(Select->list_champ,s);
            parser_eat(pars,T_ID);
            if(pars->current_token->type == T_COMA) 
                parser_eat(pars,T_COMA);
            else
                break;
        }
    }else if (pars->current_token->type == T_CHAMP){
        Select->is_all = false;
        while (strcmp(pars->current_token->value,"from") != 0)
        {
            char *s = strdup(pars->current_token->value);
            ListString_Append_Item_Str(Select->list_champ,s);
            parser_eat(pars,T_CHAMP);
            if(pars->current_token->type == T_COMA) 
                parser_eat(pars,T_COMA);
            else
                break;
        }
    }



    // FROM
    parser_verif_syntaxe(pars,"from");
    parser_eat(pars,T_ID);

    // table
    parser_eat(pars,T_ID);

    if(pars->current_token->type == T_ID){
        parser_verif_syntaxe(pars,"where");
        // WHERE
        parser_eat(pars,T_ID);
    }

    parser_parse_condition(pars, Select);

    return Select;
}

void parser_parse_condition(parser pars, ast ast){

    if(pars->current_token->type == T_ID || pars->current_token->type == T_CHAMP){
        ast->is_all_select = false;
        
        // Nom 
        if(pars->current_token->type == T_CHAMP){
            char *s = strdup(pars->current_token->value);
            ListString_Append_Item_Str(ast->list_champ_condition,s);
            parser_eat(pars,T_CHAMP);

        }else{
            char *s = strdup(pars->current_token->value);
            ListString_Append_Item_Str(ast->list_champ_condition,s);
            parser_eat(pars,T_ID);
        }

        // <
        if(is_an_op(pars->current_token->type) != -1){
            ast->list_op = calloc(1,sizeof(int*));
            ast->list_op[0] = pars->current_token->type;
            ast->list_op_size +=1; 
        }else{
            printf("Erreur , `operateur` attendu ici , actu %s\n",token_type_as_string(pars->current_token->type));
            exit(1);
        }
            parser_eat(pars,pars->current_token->type);

        // 25
        if(pars->current_token->type == T_INT || pars->current_token->type == T_STRING){
            char *s = strdup(pars->current_token->value);
            ListString_Append_Item_Str(ast->list_enter,s);
            ast->list_enter_type = calloc(1,sizeof(int*));
            ast->list_enter_type[0] = pars->current_token->type;
            parser_eat(pars,pars->current_token->type);
        }else{
            printf("Erreur , `T_INT ou T_STRING` attendu ici , actu %s\n",token_type_as_string(pars->current_token->type));
            exit(1);
        }

        return;        
    }
        ast->is_all_select = true;

        ast->list_op = calloc(1,sizeof(int*));
        ast->list_op[0] = -1;
        ast->list_op_size +=1; 

        ListString_Append_Item_Str(ast->list_enter,"*");

        ast->list_enter_type = calloc(1,sizeof(int*));
        ast->list_enter_type[0] = -1;

}

static listString parser_parse_insert_multi_data(parser pars){
    
    listString list = ListString();
    
    //(
    parser_eat(pars,T_LPARENT);

    while (pars->current_token->type != T_RPARENT)
    {
        ListString_Append_Item_Str(list,pars->current_token->value);
        parser_eat(pars,pars->current_token->type);

        if(pars->current_token->type == T_COMA) 
            parser_eat(pars,T_COMA);
        else 
            break;
    }
    //)
    parser_eat(pars,T_RPARENT);

    return list;
}


ast parser_parse_insert(parser pars){
    ast Insert = init_ast(AST_INSERT);

    // INSERT
    parser_eat(pars,T_ID);


    // INTO
    if(strcmp("into",pars->current_token->value)!=0){
        printf("Erreur, key attendu : `INTO` , actu : `%s` \n",pars->current_token->value);
        exit(1);
    }
    parser_eat(pars,T_ID);

    // TABLE
    parser_eat(pars,T_ID);

    // VALUE
    if(strcmp("value",pars->current_token->value)!=0){
        printf("Erreur, key attendu : `VALUE` , actu : `%s` \n",pars->current_token->value);
        exit(1);
    }
    parser_eat(pars,T_ID);

    listString list = parser_parse_insert_multi_data(pars);
    Insert->list_insert_value = calloc(1,sizeof(*Insert->list_insert_value));
    Insert->list_insert_value[0] = list;
    Insert->list_insert_value_size = 1;

    while (pars->current_token->type == T_COMA){
    
        parser_eat(pars,T_COMA);
        listString list = parser_parse_insert_multi_data(pars);
        Insert->list_insert_value_size += 1;
        
        Insert->list_insert_value = realloc(Insert->list_insert_value,
            Insert->list_insert_value_size *
            sizeof(*Insert->list_insert_value)
        );
    
        Insert->list_insert_value[Insert->list_insert_value_size -1] = list;
    }
    
    return Insert;
}
ast parser_parse_update(parser pars){
    ast Update = init_ast(AST_UPDATE);

    // UPDATE
    parser_eat(pars,T_ID);

    //table 
    parser_eat(pars,T_ID);

    // SET
    parser_verif_syntaxe(pars,"set");
    parser_eat(pars,T_ID);

    while (strcmp("where",pars->current_token->value) !=0){

        ListString_Append_Item_Str(Update->list_champ,pars->current_token->value);
        if(pars->current_token->type == T_CHAMP || pars->current_token->type == T_ID){
            parser_eat(pars,pars->current_token->type); // $exemple_champ ou exemple_champ
        }else{
            printf("erreur , type de champ inconnue , attendu (T_ID ou T_STRING) \n");
            exit(1);
        }

        parser_eat(pars,T_EQUAL); // =

        if(pars->current_token->type == T_INT){
            ListString_Append_Item_Str(Update->list_champ_new_value,pars->current_token->value);
            parser_eat(pars,T_INT); // INT_VALUE
        }else{
            ListString_Append_Item_Str(Update->list_champ_new_value,pars->current_token->value);
            parser_eat(pars,T_STRING); // STRING_VALUE
        }

        if(pars->current_token->type == T_SEMI)
            parser_eat(pars,T_SEMI); // SEMI , 
        else
            break;

    }
    
    parser_verif_syntaxe(pars,"where");
        parser_eat(pars,T_ID);

    parser_parse_condition(pars,Update);

    return Update;

}
ast parser_parse_delete(parser pars){

    ast Delete = init_ast(AST_DELETE);
    // DELETE
    parser_eat(pars,T_ID);
    // FROM
    parser_verif_syntaxe(pars,"from");
    parser_eat(pars,T_ID);

    parser_eat(pars,T_ID);

    if(pars->current_token->type == T_ID){
        parser_verif_syntaxe(pars,"where");
        // WHERE
        parser_eat(pars,T_ID);
    }

    parser_parse_condition(pars,Delete);
    return Delete;

}
ast parser_parse_print(parser pars){

    ast Print = init_ast(AST_PRINT);
        parser_eat(pars,T_ID);

    return Print;
}
ast parser_parse_create_table(parser pars){

}