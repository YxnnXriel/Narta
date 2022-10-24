#ifndef __NARTA_H__
#define __NARTA_H__

#include "str.h"
#include <stdio.h>




typedef struct STRUCT_CHAMP
{
    string Nom_de_champ;
}data_t , *data;


typedef struct NARTA_STRUCT{
    char * Db; // Nom de la base de donnée
    FILE* File; // nous permettre d'open la Db
    int NbrChamp; // nombre de champ
    int Count; // nombre d'element dans le fichier
    data *TabData;
}narta_t, *narta;


narta __init_narta(char *db , int NbrChamp , string champ);
data __init_data(char *nom_du_champ);
narta connect_narta(char *db);


#endif