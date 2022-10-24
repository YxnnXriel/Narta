#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/token.h"
#include "include/narta.h"




#include "include/str.h"
#include "include/request.h"



/**
 * @brief recuperation du numero de la commande
 * 
 * @param request 
 * @return int 
 */
int Get_request_number(string request){

    if (strcmp(request->str, "INSERT") == 0) return INSERT;
    else if (strcmp(request->str, "SELECT") == 0) return SELECT;
    else if (strcmp(request->str, "UPDATE") == 0) return UPDATE;
    else if (strcmp(request->str, "DELETE") == 0)return DELETE;   
    else if (strcmp(request->str, "CREATE_TABLE") == 0) return CREATE_TABLE;
    else return NONE;

}

string Get_request_str(int req_type){
    switch (req_type)
    {
        case UPDATE: return String("UPDATE");
        case INSERT: return String("INSERT");
        case DELETE: return String("DELETED");
        case CREATE_TABLE: return String("CREATE_TABLE");
        case NONE: return String("NONE");
        default:return NULL;
    }
}


/**
 * @brief Renvoie les champs de la base de donnée
 * 
 * @param narta 
 * @return string 
 */
string Get_Table_Champ(narta narta){
    narta->File = fopen(narta->Db,"r");    
    
    char Text[512];
    fgets(Text,511,narta->File);
    fclose(narta->File);

    return String(Text);
}

/**
 * @brief get la position du champ dans la base de donnée
 * 
 * @param narta 
 * @param champ_name 
 * @return int 
 */

int Get_position_in_Table(narta narta, string champ_name){
    for (int i = 0; i < narta->NbrChamp; i++){

        if (strcmp(champ_name->str, String_Get_str(narta->TabData[i]->Nom_de_champ)) == 0){
            return i;
        } 
    }
    
    return -1;
}


static bool Verif_id(char *Text , int id){
    char *chaine = strdup(Text);
    for(char *Tok =strtok(chaine," "); Tok != NULL; Tok = strtok(NULL," "))
        if(id == atoi(Tok))
            return true;

    return false;
}
static string Get_Item_by_pos_champ(char *chaine,int pos){

    listString list =  String_Split(String(chaine)," ");

    for (int i = 0; i < list->Size; i++)
        if(i == pos)
            return String(ListString_Get_Item(list,i));
    
    return NULL;
}


static string Get_data_in_fic_by_id(narta narta , int id){
    narta->File = fopen(narta->Db,"r");
    char Text[512];
    while(fgets(Text,511,narta->File) != NULL){
        if(Verif_id(Text,id)){
            fclose(narta->File);
            return String(Text);
        }
    }   

    fclose(narta->File);


    return NULL;
}


/**
 * @brief renvoie la données sous forme de chaine de caractere 
 * option 
 *  ALL : Toute les données 
 *  Champ : Ce champ
 * @param narta 
 * @param option 
 * @param id 
 * @return string 
 */
string Get_data_by_id(narta narta ,char *option ,  int id){
    narta->File = fopen(narta->Db,"r");
    char Text[512];
    while(fgets(Text,511,narta->File) != NULL){
        if(Verif_id(Text,id)){
            if(strcmp("ALL",option) == 0){
                fclose(narta->File);
                return String(Text);
            }else{
                int x = Get_position_in_Table(narta, String(option));
                if( x != -1){
                    fclose(narta->File);
                    return Get_Item_by_pos_champ(Text,x);
                }
            }
        }
    }
        
    fclose(narta->File);
    return NULL;    
}


/**
 * @brief renvoie les données sous formes de liste de champ
 * 
 * @param narta 
 * @param list_multiple 
 * @param id 
 * @return string 
 */
static string Get_data_by_id_multiple(narta narta ,listString list_multiple , int id){


    int is_all = 0;
    for (int i = 0; i < list_multiple->Size; i++)
    {
        if(strcmp("ALL",ListString_Get_Item(list_multiple,i)) ==0){
            is_all = 1;
            break;
        }
    }
    
    if(is_all == 0){
        listString list = ListString();
        for (int i = 0; i < list_multiple->Size; i++){

            string value = Get_data_by_id(narta,ListString_Get_Item(list_multiple,i),id);
            ListString_Append_Item_Str(list,value->str);
        }
        
        return String_Remont(list);
    }else{
        return Get_data_by_id(narta,"ALL",id);
    }
}


listString Evaluate_data(
    narta narta , listString souhait_value , 
    string champ , int op ,
    string enter,int type_champ){


    listString list = ListString();

    string item; 

    // printf("count = %d \n",narta->Count);
    for (int i = 1; i < narta->Count; i++){
        string is_append = Get_data_by_id_multiple(narta,souhait_value,i);
        // printf("is append = %s\n",is_append->str);
        if (type_champ != -1){
            item = Get_data_by_id(narta,champ->str,i);
            // printf("item = %s\n",item->str);
        }

        // champ < 12
        if (type_champ == T_INT){
            if(token_convert_to_type("<") == op ){
                if(atoi(item->str) < atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type("<=") == op ){
                if(atoi(item->str) <= atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type("=") == op ){
                if(atoi(item->str) == atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type(">") == op ){
                if(atoi(item->str) > atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type(">=") == op ){
                if(atoi(item->str) >= atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type("!=") == op ){
                if(atoi(item->str) != atoi(enter->str))
                    ListString_Append_Item_Str(list,is_append->str);
            }

        }else if (type_champ == T_STRING){
            if(token_convert_to_type("!=") == op ){
                if(strcmp(item->str , enter->str) != 0)
                    ListString_Append_Item_Str(list,is_append->str);
            }
            if(token_convert_to_type("=") == op ){
                if(strcmp(item->str , enter->str) == 0)
                    ListString_Append_Item_Str(list,is_append->str);
            }
        }else if (type_champ == -1){
            ListString_Append_Item_Str(list,is_append->str);
        }
    }


    return list;
    
}




static void update_in_fic_by_pos(char *file, string value , int id){
    FILE *fic = fopen(file,"r");
    FILE *temp = fopen("temp.txt","w");

    char Text[512];

    while (fgets(Text,511,fic) != NULL ){
        if(Verif_id(Text,id)){
            if(value != NULL){
                if(strstr(value->str,"\n"))
                    fprintf(temp,"%s",value->str);
                else
                    fprintf(temp,"%s\n",value->str);
            }
        }else{
            fprintf(temp,"%s",Text);
        }
    }

    fclose(fic);
    fclose(temp);
    
    remove(file);
    rename("temp.txt",file);    
    
    return;
}


/**
 * @brief Met à jour les information dans la db
 * 
 * @param narta 
 * @param value 
 * @param option 
 * @param id 
 */

void Update_data_by_id (narta narta, string value , char *option  ,int id){
    
    narta->File = fopen(narta->Db,"r");
    char Text[512];

    while(fgets(Text,511,narta->File) != NULL){
        if(Verif_id(Text,id)){
            if(strcmp("ALL",option) == 0){
                    fclose(narta->File);
                update_in_fic_by_pos(narta->Db,value , id);
                return;

            }else{

                int x = Get_position_in_Table(narta, String(option));
                if( x != -1){
                    fclose(narta->File);
                    listString nt = String_Split(Get_data_in_fic_by_id(narta,id)," \n");

                    for (int i = 0; i < nt->Size; i++)
                    {   
                        if(i == x){
                            String_Set_str(nt->ListStr[i],value->str);
                            break;
                        }
                    }

                    string g = String_Remont(nt);
                    String_Set_str(value,g->str);
            
                    update_in_fic_by_pos(narta->Db,value , id);
                    return;
                }
            }
        }
    }      

    fclose(narta->File);

}

int Update_data_by_id_multiple(narta narta, listString mult_champ ,listString new_value, int id ){
        listString list = ListString();
        for (int i = 0; i < mult_champ->Size; i++){
            Update_data_by_id(narta,
                String(ListString_Get_Item(new_value,i)),
                ListString_Get_Item(mult_champ,i),
                id
            );
        }
    
    return 1;
}


bool Is_digit(char *chaine){

    if(strcmp(chaine,"pk")==0)
        return true;
    for (int i = 0; chaine[i] != '\0'; i++)
        if(!isdigit(chaine[i]))
            return false;

    return true;    
}



int Insert_data(narta narta,string value){
    listString List = String_Split(value," ");
    if(List->Size != narta->NbrChamp)
        return -1;

    if(!Is_digit(ListString_Get_Item(List,0)))
        return -1;
    


    narta->File = fopen(narta->Db,"a+");

    for (int i = 0; i < List->Size; i++)
    {
        if(strcmp(ListString_Get_Item(List,i),"pk")==0){
            fprintf(narta->File,"%d ",Get_Id_(narta));
        }else
            fprintf(narta->File,"%s ",ListString_Get_Item(List,i));
    }
        fprintf(narta->File,"\n");
    
    narta->Count +=1;
    fclose(narta->File);


    return Ordonne_Data(narta);

}

static int copy_to(string path , string new){
        FILE *fic = fopen(path->str,"r");
        FILE *rec = fopen(new->str,"w+");

        char ch = 0;

        if(fic != NULL && rec != NULL){
            while((ch = getc(fic)) != EOF)
                putc(ch, rec);
        }

        fclose(fic);
        fclose(rec);

    return 0;
}


/**
 * @brief delete element by id
 * 
 * @param narta 
 * @param option 
 * @param id 
 */
void Delete_data_by_id(narta narta, int id){
    narta->File = fopen(narta->Db, "r");
    FILE* fic = fopen("test.txt", "w");

    if(fic != NULL && narta->File != NULL){
        char Text[512];
        while(fgets(Text,511,narta->File) != NULL){
            if(Verif_id(Text,id)){
                    string obj = String(Text);
                    // printf("this object '%s' has been de    leted from the table",obj->str );
                    narta->Count -= 1;
            }else{
                string chaine = String(Text);
                fprintf(fic, "%s",chaine->str);
            }
        }
        
            fclose(narta->File);
            fclose(fic);

            copy_to(String("test.txt"),String(narta->Db));
            remove("test.txt");
        // char *db = strdup(narta->Db);

        // if(remove(db) == 0){
        //     rename("test.txt", narta->Db);
        // }else{
        //     printf("suppression ne s'est pas bien derouler \n");
        // }

        // printf("\nici\n");

    }else{
        fclose(fic);
        fclose(narta->File);
    }

}
 


int is_exist_id_(char *file,int value){
	FILE *fic = fopen(file,"r");
	char Text[512];
	while (fgets(Text,511,fic)!=NULL)
	{
		for (char * Tok = strtok(Text," "); Tok != NULL; Tok = strtok(NULL," ")){
            if(atoi(Tok) == value){
                fclose(fic);
                return value;
            }
            break;
		}
		
	}

    fclose(fic);
	
    return -1;
}




int Get_Id_(narta narta){
    int Nbr =  narta->Count + 1;
    int id = -1;
    for (int i = 1; i < Nbr ; i++)
    {
        id = is_exist_id_(narta->Db,i);
        // printf("id = %d\n",id);
        if (id == -1)
        {
            id = i;
            break;
        }
    }

    if (id == -1)
    {
        id = Nbr;
    }



    return id; 
}

// iD Nom Note 
// 2 grace 14 
// 4 moo 19 
// 3 jean 18 
// 1 yann 12 
// 5 ram 10 

int Ordonne_Data(narta narta){


    FILE *fic = fopen("tst.txt","w+");

    string champ = Get_Table_Champ(narta);

    fprintf(fic,"%s",champ->str);
    free(champ->str);
    free(champ);
    fclose(fic);
    fic = fopen("tst.txt","a+");

    for (int i = 1; i < narta->Count; i++){
        if(is_exist_id_(narta->Db,i)){
            champ = Get_data_by_id(narta,"ALL",i);
            fprintf(fic,"%s",champ->str);
            free(champ->str);
            free(champ);
        }
    }
    fclose(fic);
    
    remove(narta->Db);
    rename("tst.txt",narta->Db);
    return 1;
}


char * EnvIs(char *s){

    string path = String(getenv("PATH"));
    listString lis = String_Split(path,";");


    for (int i = 0; i < lis->Size; i++){

        if(strstr(ListString_Get_Item(lis,i),s) !=NULL){
            return ListString_Get_Item(lis,i);
        }
    }

    return NULL;
}