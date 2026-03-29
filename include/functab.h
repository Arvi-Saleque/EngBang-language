// functab.h — Function definition table for EngBang compiler
#ifndef FUNCTAB_H
#define FUNCTAB_H

#include "ast.h"    /* FuncParamNode, AstNode, Type */

/* A registered function definition */
typedef struct FuncDef {
  char*          name;         /* owned */
  Type           return_type;
  FuncParamNode* params;       /* owned array, may be NULL */
  int            param_count;
  AstNode*       body;         /* NOT owned — same pointer as in AST */
  struct FuncDef* next;
} FuncDef;

void     functab_init(void);
void     functab_free(void);

/* Returns 1 on success, 0 if already defined */
int      functab_register(const char* name, Type ret_type,
                           FuncParamNode* params, int count,
                           AstNode* body);

FuncDef* functab_lookup(const char* name);

#endif /* FUNCTAB_H */
