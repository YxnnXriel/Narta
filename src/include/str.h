#ifndef __STR_H__
#define __STR_H__

#include <stdlib.h>


typedef struct STRUCT_STR
{
    char *str;
    int lenght;
}string_t,*string;


string String(char *str);
char String_index(string str , int index);
char *String_Get_str(string str);
int String_Get_lenght(string str);
int String_Set_str(string str , char *new_str);
int String_Set_char(string str , int index , char carac);
string String_cat(char *format , ...);


typedef struct STRUCT_LIST_STR
{
    string_t **ListStr;
    int Size;
}listString_t,*listString;

listString ListString();
int ListString_Append_Item_Str(listString list , char *value);
int ListString_Lenght_Item(listString list , int index);
char * ListString_Get_Item(listString list , int index);
int ListString_Search_Item_Str(listString list , char *value);
int ListString_Delete_Item(listString list , int index);
int ListString_Clear_Item(listString list);


listString String_Split(string str , char *delim);
string String_Remont(listString list);


#endif