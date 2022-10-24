#ifndef __PARSER_H__
#define __PARSER_H__
#include "lexer.h"
#include "ast.h"


typedef struct PARSER_STRUCT
{
    lexer lex;
    token current_token;
    token prev_token;
}parser_t,*parser;



int parser_verif_syntaxe(parser pars,char *cmd);


parser init_parser(lexer lex);
void parser_eat(parser pars, int type);
ast parser_parse_token_id(parser pars);
ast parser_parse(parser pars);
ast parser_parse_statements(parser pars);
ast parser_parse_statement(parser pars);
ast parser_parse_select(parser pars);
ast parser_parse_insert(parser pars);
ast parser_parse_update(parser pars);
ast parser_parse_delete(parser pars);
ast parser_parse_create_table(parser pars);
ast parser_parse_print(parser pars);
void parser_parse_condition(parser pars, ast ast);





#endif