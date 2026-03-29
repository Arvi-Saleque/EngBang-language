// tac.h — Three-Address Code generation interface
#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* Walk the AST and emit TAC to stdout.
   Requires the symbol table to be populated by semantic_check first
   (for type information on variable references). */
void tac_generate(AstNode* root);

#endif /* TAC_H */
