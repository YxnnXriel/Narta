#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/conio2.h"
#include "include/narta.h"
#include "include/shell.h"
#include "include/visitor.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/request.h"

static int information(){


    char *env = EnvIs("AutoCoding");

    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
        return 1;
    }
    
    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
        
        puts("The localtime() function failed");
        return 1;
    }
    
    // printf("The time is: %02d:%02d:%02d\n", ptm->tm_hour, 
    //        ptm->tm_min, ptm->tm_sec);


    textcolor(RED);printf("Narta 1.0.1");textcolor(WHITE);
    printf(" %02d:%02d:%02d\n", ptm->tm_hour, 
           ptm->tm_min, ptm->tm_sec);

    textcolor(YELLOW);printf("[GCC 12.1.4]");textcolor(WHITE);
    printf(" on Windows\n");
    printf("Type \"copyright\" , \"credits\" or \"license()\" for more information.\n");

    if(env != NULL){
        string vers = String_cat("%s\\version.txt",env);
        FILE *fic = fopen(vers->str,"r");
        char text[50];
        fgets(text,49,fic); 
        textcolor(GREEN);printf("%s\n",text);textcolor(WHITE);

        fclose(fic);
        free(vers->str);
        free(vers);
    }
}
void Pronpt(){
    printf(">>> ");
}

shell init_shell(){
    shell sh = calloc(1,sizeof(*sh));
    sh->narta = NULL;
    return sh;
}
void Shell_while_or_init(){
    information();

    shell sh = init_shell();

    int loop = 1;
    char *request = (void*)0;

    while (loop){
        request = Shell_render_request();

        lexer lex = init_lexer(request);
        parser pars = init_parser(lex);

        if(strcmp(pars->current_token->value,"create") == 0){
        // create [non de la base de donnée] ->  [Champs];
            parser_eat(pars,T_ID); // create
            char *bs_name = pars->current_token->value;

            parser_eat(pars,T_ID); // db
            parser_eat(pars,T_TIRET); // -
            parser_eat(pars,T_SUP); // >

            parser_eat(pars,T_LBRACE); // [
            listString list_champ = ListString();
            ListString_Append_Item_Str(list_champ,pars->current_token->value);
            parser_eat(pars,T_ID); // Nom

            while (pars->current_token->type == T_COMA){
                parser_eat(pars,T_COMA);
                ListString_Append_Item_Str(list_champ,pars->current_token->value);
                parser_eat(pars,T_ID); // ect..
            }
            parser_eat(pars,T_RBRACE); // ]

            string new_bs = String_cat("%s.txt",bs_name);

            sh->narta = __init_narta(new_bs->str,list_champ->Size,String_Remont(list_champ));

            free(new_bs->str);
            free(new_bs);
            free(lex);
            free(pars);
            loop = 0;
        }else if(strcmp(pars->current_token->value,"connect") == 0){

            parser_eat(pars,T_ID);
            char *db = pars->current_token->value;
            string new_bs = String_cat("%s.txt",db);
            sh->narta = connect_narta(new_bs->str);

            free(new_bs->str);
            free(new_bs);
            free(lex);
            free(pars);
            loop = 0;

        }else if(strcmp(pars->current_token->value,"cls")==0){
            system("cls");
            free(lex);
            free(pars);
            information();
        }else if(strcmp(pars->current_token->value,"exit")==0){
            free(lex);
            free(pars);
            free(request);
            loop = 0;
            exit(1);
        }

        free(request);
    }

    if(sh->narta != NULL){
        while (1){
            request =  Shell_render_request();
            
            if(strstr(request,"cls") != NULL){
                clrscr();
                information();
            }else if(strstr(request,"count") != NULL){
                printf("Count : %d \n",sh->narta->Count-1);
            }else if(strstr(request,"get table") !=NULL){
                string chaine = Get_Table_Champ(sh->narta);
                printf("table : %s",chaine->str);
            }else if(strstr(request,"narta man") !=NULL){
                textcolor(RED); printf("MAN NARTA\n");textcolor(WHITE);
                printf("SELECT .... FROM table WHERE condition\n");
	            printf("UPDATE table Set $rue = '99' , blabla Where id = 2\n");
	            printf("DELETE FROM table where condition\n");
	            printf("CREATE TABLE utilisateur {id:int , nom:text,prenom:text}\n");
	            printf("INSERT INTO TABLE VALUE (,,,,)\n");
            }else{
                lexer lex = init_lexer(request);
	            parser pars = init_parser(lex);
	            ast ast = parser_parse(pars);
	            // printf("ast -> %d \n",ast->coumpoud_size);

	            listString res = visito_visit(ast,sh->narta);
	            // printf("res -> %s \n",ListString_Get_Item(res,0));
            }
            free(request);
        }
    }


}
char *Shell_render_request(){
    
    char *text = calloc(512,sizeof(char*)); 
    Pronpt();

    fflush(stdin);
    gets(text);
    fflush(stdin);

    return text;
}