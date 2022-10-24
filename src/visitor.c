#include <stdio.h>
#include <stdlib.h>
#include "include/visitor.h"
#include "include/ast.h"
#include "include/request.h"
#include "include/token.h"
#include "include/utile.h"

listString visito_visit(ast as , narta narta){

    switch (as->type)
    {
        case AST_COUPOUND : return visito_visit_coumpond(as,narta); break;
        case AST_SELECT :  return visito_visit_select(as,narta); break;    
        case AST_INSERT : return visito_visit_insert(as,narta); break;    
        case AST_UPDATE : return visito_visit_update(as,narta); break;    
        case AST_DELETE : return visito_visit_delete(as,narta); break;    
        case AST_PRINT : return visito_visit_print(as,narta); break;    
        
        default:
            break;
    }   
    printf("return \n");
    return ListString();
}
listString visito_visit_coumpond(ast as,narta narta){

    for (int i = 0; i < as->coumpoud_size; i++)
    {
        visito_visit(as->coumpoud[i],narta);
    }

    return ListString();
}

listString visito_visit_print(ast as,narta narta){


        // for (int i = 1; i < narta->Count; i++){
        //     string chaine = Get_data_by_id(narta,"ALL",i);
        // }
        
    // printf("ici");
    TextTable(narta->Db,narta->Count,narta->NbrChamp);
    return ListString();
}


listString visito_visit_select(ast as,narta narta){

    listString list;
    if(as->is_all == 0){
        

            for (int i = 0; i < as->list_champ->Size; i++)
            {
                if(Get_position_in_Table(narta,String(ListString_Get_Item(as->list_champ,i))) == -1){
                    printf("Erreur , `%s` n'est pas un champ de la base de donnees \n",
                        ListString_Get_Item(as->list_champ,i)
                    );
                    exit(1);
                }
            }

            for (int i = 0; i < as->list_champ->Size; i++)
            {
                printf("liste champ :%s\n",ListString_Get_Item(as->list_champ,i));
            }
        

        list = Evaluate_data(
            narta,
            as->list_champ,
            String(ListString_Get_Item(as->list_champ_condition,0)),
            as->list_op[0],
            String(ListString_Get_Item(as->list_enter,0)),
            as->list_enter_type[0]
        );
        
    }else{
        // printf("%d %s\n",as->list_enter_type[0],ListString_Get_Item(as->list_enter,0));

        list = Evaluate_data(
            narta,
            as->list_champ,
            String(ListString_Get_Item(as->list_champ_condition,0)),
            as->list_op[0],
            String(ListString_Get_Item(as->list_enter,0)),
            as->list_enter_type[0]
        );


    }

    for (int i = 0; i < list->Size; i++)
    {
        printf(" list = %s\n",ListString_Get_Item(list,i));
    }

    
    // printf("icic ii\n");
    // printf("%s %d %s\n" , ListString_Get_Item(as->list_champ_condition,0),
    //     as->list_op[0],
    //     ListString_Get_Item(as->list_enter,0)
    // );
    return list;

}
listString visito_visit_insert(ast as,narta narta){


    for(int i  = 0; i < as->list_insert_value_size ; i++){
        if(narta->NbrChamp != as->list_insert_value[i]->Size){
            if(narta->NbrChamp < as->list_insert_value[i]->Size)
                printf("Erreur, trop d'argment en entrer \n");
            else
                printf("Erreur, argment manquant \n");
            exit(1);
        }


    }

    for (int i = 0; i < as->list_insert_value_size; i++){
        Insert_data(narta,String_Remont(as->list_insert_value[i]));
    }


    return ListString();
}
listString visito_visit_update(ast as,narta narta){
    // mise à jour des données

        for (int i = 0; i < as->list_champ->Size; i++){
            if(Get_position_in_Table(narta,String(ListString_Get_Item(as->list_champ,i))) == -1){
                printf("Erreur , `%s` n'est pas un champ de la base de donnees \n",
                    ListString_Get_Item(as->list_champ,i)
                );
                exit(1);
            }
        }

    
        //printf("%d %d \n",as->list_champ_new_value->Size, as->list_champ->Size);
       if(as->list_champ_new_value->Size != as->list_champ->Size){
            printf("Erreur des manques \n");
            exit(1);
        }


        listString upda = ListString();

        ListString_Append_Item_Str(upda,"iD");
        listString list = Evaluate_data(
            narta,
            upda,
            String(ListString_Get_Item(as->list_champ_condition,0)),
            as->list_op[0],
            String(ListString_Get_Item(as->list_enter,0)),
            as->list_enter_type[0]
        );
        
        for (int i = 0; i < list->Size; i++){
            // printf(" list = %d \n",atoi(ListString_Get_Item(list,i)));
            Update_data_by_id_multiple(narta,as->list_champ,as->list_champ_new_value,atoi(ListString_Get_Item(list,i)));
        }
        printf("\n");

    return ListString();
}
listString visito_visit_delete(ast as,narta narta){
        listString del = ListString();

        ListString_Append_Item_Str(del,"iD");
        listString list = Evaluate_data(
            narta,
            del,
            String(ListString_Get_Item(as->list_champ_condition,0)),
            as->list_op[0],
            String(ListString_Get_Item(as->list_enter,0)),
            as->list_enter_type[0]
        );

    
    // printf("size = %d\n",list->Size);
    for (int i = 0; i < list->Size; i++)
    {
        // printf(" list = %s \n",ListString_Get_Item(list,i));
        Delete_data_by_id(narta,atoi(ListString_Get_Item(list,i)));
    }
    printf("\n");

    
    return ListString();
}