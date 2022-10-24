#ifndef __REQUEST_H__
#define __REQUEST_H__


#include <stdbool.h>

typedef enum{
    INSERT,
    SELECT,
    UPDATE,
    DELETE,
    CREATE_TABLE,
    NONE= -1,
}Cmd;


int Get_request_number(string request); // renvoie la commande de la requete sous forme de chiffre
string Get_request_str(int req); // renvoie la commande de la requete sous forme de chaine 
string Get_Table_Champ(narta narta); // renvoie les champs sous forme de chaine de caractere
int Get_position_in_Table(narta narta, string champ_name);
string Get_data_by_id(narta narta,char *option  ,int id); // renvoie la données en fonction de l'id


void Update_data_by_id (narta narta, string value , char *option  ,int id); // met à jour des données

void Delete_data_by_id(narta narta, int id);

int Insert_data(narta narta,string value);
bool Is_digit(char *chaine);

listString Evaluate_data(
    narta narta , 
    listString souhait_value , 
    string champ , 
    int op ,
    string enter,
    int type_champ
);
int Update_data_by_id_multiple(narta narta, listString mult_champ ,listString new_value, int id );



int is_exist_id_(char *file,int value);
int Get_Id_(narta narta);
int Ordonne_Data(narta narta);
char * EnvIs(char *s);

#endif