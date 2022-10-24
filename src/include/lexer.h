#ifndef __LEXER_H__
#define __LEXER_H__


#include "token.h"

typedef struct LEXER_STRUCT
{
    char *src;
    int i;
    char current_char;
}lexer_t,*lexer;


lexer init_lexer(char *cmd);
void lexer_advance(lexer lex);
void lexer_skip_white_space(lexer lex);
token GetNextToken(lexer lex);
token lexer_collect_int(lexer lex);
token lexer_collect_id(lexer lex);
token lexer_collect_string(lexer lex);
token lexer_collect_champ(lexer lex);

token lexer_advance_with_token(lexer lex , int type , char *value);
char *lexer_make_as_string(lexer lex);





#endif