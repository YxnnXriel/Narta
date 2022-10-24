#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <stdbool.h>

#include "include/lexer.h"

#define or ||
#define and &&


lexer init_lexer(char *cmd){
    lexer lex = calloc(1,sizeof(*lex));
    lex->src = strdup(cmd);
    lex->i = 0;
    lex->current_char = lex->src[strlen(cmd)>= 1 ? 0:0 ];
    return lex;
}

void lexer_advance(lexer lex){
    if (lex->i < strlen(lex->src) && lex->current_char != '\0')
    {
        lex->i +=1;
        lex->current_char = lex->src[lex->i];
    }
}
void lexer_skip_white_space(lexer lex){
    while (lex->current_char == ' ' or lex->current_char == '\t' or lex->current_char == '\r'){
        lexer_advance(lex);
    }
}


bool lexer_peek(lexer lex , char look){
    if(lex->i +1 < strlen(lex->src) || lex->src[lex->i +1] != '\0'){
        if(lex->src[lex->i +1] == look){
            lexer_advance(lex);
            return true;
        }
    }
    return false;
}



token GetNextToken(lexer lex){
    if(lex->current_char != '\0' or lex->i < strlen(lex->src)){
        lexer_skip_white_space(lex);
        
        if(isdigit(lex->current_char))
            return lexer_collect_int(lex);
        if(isalnum(lex->current_char))
            return lexer_collect_id(lex);
        if(lex->current_char == '"')
            return lexer_collect_string(lex);
        
        if(lex->current_char == '$')
            return lexer_collect_champ(lex);

        switch (lex->current_char)
        {
            case '=' : return lexer_advance_with_token(lex,T_EQUAL,"="); break;
            case '-' : return lexer_advance_with_token(lex,T_TIRET,"-"); break;
            case '<' : return lexer_peek(lex,'=') == true ?  lexer_advance_with_token(lex,T_INF_EQUAL,"<=")
                        :lexer_advance_with_token(lex,T_INF,"<");
            case '>' : return lexer_peek(lex,'=') == true ?  lexer_advance_with_token(lex,T_SUP_EQUAL,">=")
                        :lexer_advance_with_token(lex,T_SUP,">");
            case '!' : return lexer_peek(lex,'=') == true ?  lexer_advance_with_token(lex,T_DIFF,"!=")
                        :lexer_advance_with_token(lex,T_EOF,"\0");
            case '&' : return lexer_peek(lex,'&') == true ?  lexer_advance_with_token(lex,T_AND,"&&")
                        :lexer_advance_with_token(lex,T_EOF,"\0");
            case '|' : return lexer_peek(lex,'|') == true ?  lexer_advance_with_token(lex,T_OR,"||")
                        :lexer_advance_with_token(lex,T_EOF,"\0");
            case '(' : return lexer_advance_with_token(lex,T_LPARENT,"("); break;
            case ')' : return lexer_advance_with_token(lex,T_RPARENT,")"); break;
            case '[' : return lexer_advance_with_token(lex,T_LBRACE,"["); break;
            case ']' : return lexer_advance_with_token(lex,T_RBRACE,"]"); break;
            case '*' : return lexer_advance_with_token(lex,T_ASTERISK,"*"); break;
            case ';' : return lexer_advance_with_token(lex,T_SEMI,";"); break;
            case ',' : return lexer_advance_with_token(lex,T_COMA,","); break;
            default:break;;
        }
    }

    // return NULL;
    return lexer_advance_with_token(lex,T_EOF,"\0");
}




token lexer_advance_with_token(lexer lex , int type , char *value){
        token tok = init_token(type,value);
        lexer_advance(lex);
        return tok;
}


token lexer_collect_champ(lexer lex){
    lexer_advance(lex);

    char *s = lexer_make_as_string(lex);
    lexer_advance(lex);
    while (isalnum(lex->current_char))
    {
        char *value = lexer_make_as_string(lex);
        s = realloc(s,(strlen(s) + strlen(value) + 1) * sizeof(char*));
        strcat(s,value);
        lexer_advance(lex);
    }

    return init_token(T_CHAMP,s);
}



token lexer_collect_string(lexer lex){
    lexer_advance(lex);

    char *s = lexer_make_as_string(lex);
    lexer_advance(lex);
    while (lex->current_char != '"')
    {
        char *value = lexer_make_as_string(lex);
        s = realloc(s,(strlen(s) + strlen(value) + 1) * sizeof(char*));
        strcat(s,value);
        lexer_advance(lex);
    }

    lexer_advance(lex);
    return init_token(T_STRING,s);
    
}

token lexer_collect_id(lexer lex){

    // NOM 
    char *s = lexer_make_as_string(lex);

    lexer_advance(lex);
    while (isalnum(lex->current_char))
    {
        char *value = lexer_make_as_string(lex);
        s = realloc(s,(strlen(s) + strlen(value) + 1) * sizeof(char*));
        strcat(s,value);
        lexer_advance(lex);
    }
    

    return init_token(T_ID,s);

}

token lexer_collect_int(lexer lex){
    // 122

    char *s = lexer_make_as_string(lex);

    lexer_advance(lex);
    while (isdigit(lex->current_char))
    {
        char *value = lexer_make_as_string(lex);
        s = realloc(s,(strlen(s) + strlen(value) + 1) * sizeof(char*));
        strcat(s,value);
        lexer_advance(lex);
    }
    

    return init_token(T_INT,s);

}


char *lexer_make_as_string(lexer lex){
    char *s = calloc(2,sizeof(char*));
    s[0] = lex->current_char;
    s[1] = '\0';

    return s;
}

