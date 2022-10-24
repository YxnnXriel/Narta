#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "include/str.h"


/**
 * @brief Constructeur de String
 * 
 * @param str 
 * @return string 
 */
string String(char *str){
    string string = calloc(1,sizeof(*string));
    
    if(str != NULL){
        string->str = strdup(str);
        string->lenght = strlen(str); 
    }else{
        string->str = NULL;
        string->lenght = 0;
    }

    return string;    
}


/**
 * @brief Donne le caractère actuelle
 * 
 * @param str 
 * @param index 
 * @return char 
 */
char String_index(string str , int index){
    return str->lenght >= index ? str->str[index] : 0;
}


/**
 * @brief Retourne la chaine actuelle,Parfait pour L'affichage
 * 
 * @param str 
 * @return char* 
 */
char *String_Get_str(string str){
    return str->str != NULL ? str->str:NULL;
}


/**
 * @brief Renvoi la longueur de la chaine actuelle
 * 
 * @param str 
 * @return int 
 */
int String_Get_lenght(string str){
    return str->lenght;
}

/**
 * @brief Modifie la chaine actuelle
 * 
 * @param str 
 * @param new_str 
 * @return int 
 */
int String_Set_str(string str , char *new_str){
    str->str = strdup(new_str);
    str->lenght = strlen(new_str);
    return str->lenght == 0 ? 0:str->lenght;
}

/**
 * @brief Modifie le caractere de la chaine à l'index donner
 * 
 * @param str 
 * @param index 
 * @param carac 
 * @return int 
 */
int String_Set_char(string str , int index , char carac){
    if (str->lenght >= index)
    {
        str->str[index] = carac;
        return index;
    }
    return -1;
}


/**
 * @brief Decoupe la chaine et renvoi sous forme de liste de chaine de caractère
 * 
 * @param str 
 * @param delim 
 * @return listString 
 */
listString String_Split(string str , char *delim){
    
    char *s = String_Get_str(str);
    listString list = ListString();

    for (char *Tok = strtok(s,delim); Tok != NULL ; Tok = strtok(NULL,delim))
        ListString_Append_Item_Str(list,Tok);

    return list;
}


string String_cat(char *format , ...){
    /**
    *  %s string format
    *  %d int format
    *  %f float format
    */

    va_list args;
    va_start(args,format);

    char Buffer[BUFSIZ];


    vsprintf(Buffer,format,args);
    va_end(args);
    return String(Buffer);
}


string String_Remont(listString list){
    int len = 0;
    len += list->Size;
    for (int i = 0; i < list->Size; i++)
    {
        len += ListString_Lenght_Item(list,0);
    }

    char *s = calloc(len,sizeof(char*));

    for (int i = 0; i < list->Size; i++)
    {
        strcat(s,ListString_Get_Item(list,i));
        strcat(s," ");
    }
    

    return String(s);

}

/* ------------------LIST STRING---------------------- */




/**
 * @brief Constructeur de listString
 * 
 * @return listString 
 */
listString ListString(){
    listString list = calloc(1,sizeof(*list));
    list->Size = 0;
    list->ListStr = (void *)0;
    return list;
}



/**
 * @brief Ajoute une chaine à la liste
 * 
 * @param list 
 * @param value 
 * @return int 
 */
int ListString_Append_Item_Str(listString list , char *value){
        list->Size++;

        list->ListStr = list->ListStr == (void*)0 ? 
        calloc(list->Size,sizeof(list->ListStr)):
        realloc(list->ListStr, list->Size * sizeof(list->ListStr));

        list->ListStr[list->Size -1] = String(value);

    return 1;
}


/**
 * @brief Renvoi la longueur de la chaine à l'index passer en parametre
 * 
 * @param list 
 * @param index 
 * @return int 
 */
int ListString_Lenght_Item(listString list , int index){
    return list->ListStr != NULL && list->Size >= index ? String_Get_lenght(list->ListStr[index]) : 0; 
}


/**
 * @brief Renvoi la chaine dans la liste à l'indice passer en parametre
 * 
 * @param list 
 * @param index 
 * @return char* 
 */
char * ListString_Get_Item(listString list , int index){
    return list->ListStr != NULL && list->Size >= index ? String_Get_str(list->ListStr[index]) : NULL;    
}



/**
 * @brief Rechercher une chaine en fonction d'une autre chaine
 * 
 * @param list 
 * @param value 
 * @return int 
 */
int ListString_Search_Item_Str(listString list , char *value){
    for (int i = 0; i < list->Size; i++)
        if(strcmp(value,ListString_Get_Item(list,i)) ==0)
            return i;

    return -1;    
}


/**
 * @brief Supprime une chaine à l'index passer en parametre
 * 
 * @param list 
 * @param index 
 * @return int 
 */

int ListString_Delete_Item(listString list , int index){
    if(index <= list->Size ){
        int x = ListString_Search_Item_Str(list,ListString_Get_Item(list,index));
        for (int i = x; i < list->Size -1; i++)
            list->ListStr[i+1] = list->ListStr[i]; 

        
        list->Size--;
        list->ListStr = realloc(list->ListStr,sizeof(*list->ListStr) *list->Size );
        return 1;
    }

    return 0;
}

/**
 * @brief Supprime tous les elements de la liste
 * 
 * @param list 
 * @return int 
 */
int ListString_Clear_Item(listString list){
    int x = list->Size;
    for (int i = 0; i < x; i++)
    {
        ListString_Delete_Item(list,i);
    }


    free(list);
    list->Size = 0;
    return 1;
    
}
