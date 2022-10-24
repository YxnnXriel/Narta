#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/utile.h"

char **AutoTab2D(int x , int y){
        char **chaine = calloc(x,sizeof(*chaine));
    if(chaine == NULL){
        printf("Probleme AutoTab2D (1)");
        exit(1);
        }
        for (int i = 0; i < x; i++){
                chaine[i] = calloc(y,sizeof(*chaine));
            if(chaine[i] == NULL){
                printf("Probleme AutoTab2D (2)");
                exit(1);
        }
    }

    return chaine;
}
void DelTab2D(char **chaine,int x , int y ){
        for (int i = 0; i < x; i++)
        free(chaine[i]);

    free(chaine);
}

char ***AutoTab3D(int x , int y , int z){


    char ***chaine = calloc(x,sizeof(*chaine));
    if(chaine == NULL){
        printf("Probleme AutoTab3D (1)");
        exit(1);
        }

        for (int i = 0; i < x; i++){
                chaine[i] = calloc(y,sizeof(*chaine));
            if(chaine[i] == NULL){
                printf("Probleme AutoTab3D (2)");
                exit(1);
        }
    }

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            chaine[i][j] = calloc(z,sizeof(*chaine));
            if (chaine[i][j] == NULL){
                printf("Probleme AutoTab3D (3)");
                exit(1);
            }
        }
    }
    return chaine;
}
void DelTab3D(char ***chaine,int x , int y , int z){

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            free(chaine[i][j]);
    for (int i = 0; i < x; i++)
        free(chaine[i]);
    free(chaine);

}

void AffSpace(int x){
    for (int i = 0; i < x; i++)
    {
        printf(" ");
    }

}

size_t lenV(const char *tab){
        size_t i =0;
        for (i = 0; tab[i] !='\0'; i++);

        return i;
}


void DrawTable(int Len[] ,int eachLen[], int LenTable,char **tab, char a){
        if(a == '+'){ // du genre :  +-----+----+
                int j = 0;
                for (int i = 0; i < LenTable ; i++)
                {
                        if (Len[j] == i){
                                printf("+");
                                j++;
                        }
                        else
                                printf("-");
                        if(i == LenTable-1)
                                printf("+");
                }

        }
        else if(a == '|'){ // du genre : |         |     |
                int j = 0;
                for (int i = 0; i < LenTable ; i++)
                {
                        if (Len[j] == i){
                                printf("| %s ",tab[j]);
                                int calc = eachLen[j+1] - lenV(tab[j]);
                                j++;
                                for (int m = 0; m < calc; m++)
                                {
                                        printf(" ");
                                }
                        }
                        else
                                printf("");
                        if(i == LenTable-1)
                                printf("|");
                }
        }
}



void tsoding(char ***value,int lx ,int cy,char *file){
        unit_8 lenVaLue[lx][cy];// la taille des differents chaines

        unit_8 *MostlenVaLue = calloc(lx+1,sizeof(unit_8));// la plus grande de toutes les valeurs ajouter a son précédent
        unit_8 *EachLenVaLue = calloc(lx+1,sizeof(unit_8)); // la plus grande de chaque colonne de ligne

        for (int i = 0; i <lx; i++){
                for (int j = 0; j < cy; j++){
                        lenVaLue[i][j] = lenV(value[i][j]);
                }
        }


        MostlenVaLue[0] = 0;
        EachLenVaLue[0] = 0;

        int sva = 0;
        for (int i = 1; i < (cy+1); i++)
        {
                int tmp = lenVaLue[0][i-1];
                MostlenVaLue[i] = tmp;

                for (int j = 0; j < lx; j++)
                        if (tmp < lenVaLue[j][i-1])
                                tmp = lenVaLue[j][i-1];

                sva += tmp+3;
                EachLenVaLue[i] = tmp;
                MostlenVaLue[i] = sva;
        }




        char *s[lx];
        char Text[512];

        FILE *fic = fopen(file,"r");
        int p = 0;
        for (int i = 0; i < lx; i++)
        {
                fgets(Text,511,fic);
                for (char *Tok = strtok(Text," \n"); Tok != NULL; Tok = strtok(NULL," \n")){
                        s[p] = strdup(Tok);
                        p++;
                }
                p = 0;

                DrawTable(MostlenVaLue,EachLenVaLue,sva,s,'+');printf("\n");
                DrawTable(MostlenVaLue,EachLenVaLue,sva,s,'|');printf("\n");
        }

        DrawTable(MostlenVaLue,EachLenVaLue,sva,s,'+');printf("\n");
        fclose(fic);
        // DelTab2D(s,lx,cy);
        free(MostlenVaLue);
        free(EachLenVaLue);
}

void TextTable(char *File,int lx ,int cy){

        char ***value = AutoTab3D(lx,cy,25);

        FILE *fic = fopen(File,"r");
        if (fic != NULL){
                for (int i = 0; i < lx; i++)
                        for (int j = 0; j < cy; j++){
                                fscanf(fic,"%s",value[i][j]);
                        }

        		fclose(fic);
				
                tsoding(value,lx,cy,File);
                DelTab3D(value,lx,cy,25);

        }
        else
                printf("Erreur d'ouverture du fichier [%s] ",File);

        fclose(fic);
}

void appendTextTable(const char *file,const char chaine[]){
        FILE *fic =fopen(file,"a");
        if (fic !=NULL)
        {
                fprintf(fic,"%s",chaine);
                fprintf(fic,"\n");
        }
        else
                printf("Erreur d'ouverture du fichier [%s] ",file);

        fclose(fic);
}