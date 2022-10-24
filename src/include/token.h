#ifndef __TOKEN_H__
#define __TOKEN_H__


// select * form table where [iD] == 2 && [Nom] == 22
// select Nom,Prenom form table where [iD] == 2 
// select Nom,Prenom form table where strcmp(Nom,"la chaine") 



typedef struct TOKEN_STRUCT
{
    enum{
        T_ID,
        T_INT,
        T_STRING,    
        T_ASTERISK, // *
        T_LBRACE, // [
        T_RBRACE, // ]
        T_OR,// ||
        T_AND,// &&
        T_COMA, // ,
        T_INF, // <
        T_SUP,// >
        T_EQUAL,// = 
        T_SUP_EQUAL, // >=
        T_INF_EQUAL, // <=
        T_DIFF, // !=
        T_LPARENT, // (
        T_RPARENT, // )
        T_EOF,
        T_CHAMP,
        T_TIRET,
        T_SEMI,
    }type;
    char *value;
}token_t,*token;

token init_token(int type , char *value);
char *token_type_as_string(int type);
int token_convert_to_type(char *s);


#endif