#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/narta.h"
#include "include/str.h"
#include "include/request.h"

data __init_data(char *nom_du_champ){
    data data = calloc(1,sizeof(*data));

    data->Nom_de_champ = String(nom_du_champ);

    return data;
}

narta __init_narta(char *db , int NbrChamp , string champ){
    narta narta = calloc(1,sizeof(*narta)); 
    narta->Db = strdup(db);
    narta->NbrChamp = NbrChamp;    

    narta->TabData = calloc(NbrChamp,sizeof(*narta->TabData));

    listString listchamp = String_Split(champ, " ");

    narta->File = fopen(narta->Db, "w+");

    for (int i = 0; i < listchamp->Size; i++)
    {
        narta->TabData[i] = __init_data(ListString_Get_Item(listchamp,i));
        fprintf(narta->File, "%s ", ListString_Get_Item(listchamp,i));
    }

    fprintf(narta->File, "\n");

    fclose(narta->File);
    narta->Count = 1;

    return narta;
}

narta connect_narta(char *db){
    narta narta = calloc(1,sizeof(*narta)); 
    narta->Db = strdup(db);

    string s = Get_Table_Champ(narta);

    listString list = String_Split(s," \n");
    narta->NbrChamp = list->Size;
    narta->TabData = calloc(list->Size,sizeof(*narta->TabData));

    for (int i = 0; i < list->Size; i++){
        narta->TabData[i] = __init_data(ListString_Get_Item(list,i));    
    }

    narta->File = fopen(narta->Db, "r");

    char Txt[512];
    narta->Count = 0;
    while (fgets(Txt,511,narta->File) !=NULL)
        narta->Count++;

    fclose(narta->File);
    return narta;
}