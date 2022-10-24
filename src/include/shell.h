#ifndef __SHELL_H__
#define __SHELL_H__

// les fonction pour render le shell

#include "narta.h"

void Pronpt();
/*
    Narta 1.0.1 (la date)
    [GCC 12.1.4] on Windows
    Type "copyright" , "credits" or "license()" for more information.
    AutoCoding 2.3
    >>>
*/
// shell 

typedef struct SHELL_STRUCT{
    narta narta;
}shell_t,*shell;

shell init_shell();
void Shell_while_or_init();
char *Shell_render_request();






#endif // __SHELL_H__
