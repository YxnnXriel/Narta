#ifndef __VISITOR_H__
#define __VISITOR_H__


#include "str.h"
#include "ast.h"
#include "narta.h"
#include <stdbool.h>


listString visito_visit(ast as,narta narta);
listString visito_visit_coumpond(ast as,narta narta);
listString visito_visit_select(ast as,narta narta);
listString visito_visit_insert(ast as,narta narta);
listString visito_visit_update(ast as,narta narta);
listString visito_visit_delete(ast as,narta narta);
listString visito_visit_print(ast as,narta narta);




#endif