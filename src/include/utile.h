#ifndef __UTILE_H__
#define __UTILE_H__


typedef int unit_8;
typedef int unit_32;

char **AutoTab2D(int x , int y);
void DelTab2D(char **chaine,int x , int y );

char ***AutoTab3D(int x , int y , int z);
void DelTab3D(char ***chaine,int x , int y , int z);
void Draw3D(char ***chaine,int x , int y);

size_t lenV(const char *tab);
void appendTextTable(const char *file,const char chaine[]);
void TextTable(char *File,int lx ,int cy);
void tsoding(char ***value,int lx ,int cy,char *file);
void DrawTable(int Len[] ,int eachLen[], int LenTable,char **tab, char a);


#endif