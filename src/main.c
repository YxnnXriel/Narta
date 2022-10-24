/**
 * @file main.c	
 * @author YxnnXriel (yannariel13@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
	SELECT .... FROM table WHERE condition
	UPDATE table Set $rue = '99' , blabla Where id = 2
	DELETE FROM table where condition
	CREATE TABLE utilisateur {id:int , nom:text,prenom:text}
	INSERT INTO TABLE VALUE (,,,,)
*/

#include <stdio.h>
#include <stdlib.h>
#include "include/narta.h"
#include "include/request.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/shell.h"

int main(int argc ,char const *argv[]){

	Shell_while_or_init();
	




	// narta narta = __init_narta("text.txt",5,String("iD Nom Prenom Age Majeur"));
	// Insert_data(narta, String("1 Yann Ariel 21 none"));
	// Insert_data(narta, String("2 jean michel 15 none"));
	// Insert_data(narta, String("3 Grace carmen 17 none"));
	// Insert_data(narta, String("4 Tourer Mohamed 20 none"));
	// Insert_data(narta, String("5 Kouame Wakablet 20 none"));
	// Insert_data(narta, String("6 Onsiaho Alban 19 none"));
	// Insert_data(narta, String("7 Marc Alix 18 none"));

	// // // Delete_data_by_id(narta, 1);
	// // Update_data_by_id(narta,String("Narta"),"Nom",2);

	// // string chaine = Get_data_by_id(narta,"prenom",1);

	// lexer lex = init_lexer("PRINT;UPDATE table SET $Majeur = \"oui\" WHERE Age <= 18;PRINT");

	// parser pars = init_parser(lex);
	// ast ast = parser_parse(pars);

	// printf("ast -> %d \n",ast->coumpoud_size);

	// listString res = visito_visit(ast,narta);

	
	// printf("res -> %s \n",ListString_Get_Item(res,0));

	

	return 0;
}