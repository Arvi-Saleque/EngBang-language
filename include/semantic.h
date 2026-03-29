// semantic.h — Semantic analysis pass interface
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* Walk the AST, validate types and declarations using the global symtab.
   Populates the symtab with all declared symbols as a side effect.
   Returns the number of semantic errors found (0 = clean). */
int semantic_check(AstNode* root);

#endif /* SEMANTIC_H */
