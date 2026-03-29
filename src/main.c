/* main.c — EngBang compiler entry point.
 *
 * Pipeline:
 *   1. yyparse()          -> builds AST (parser.y / lexer.l)
 *   2. semantic_check()   -> type validation, populates symtab
 *   3. tac_generate()     -> emits Three-Address Code to stdout
 *   4. exec_program()     -> interprets the validated AST
 */
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "symtab.h"
#include "functab.h"
#include "semantic.h"
#include "tac.h"

/* Defined in the Bison-generated parser */
extern int     yyparse(void);
extern AstNode* g_parse_result;

/* Defined in exec.c */
void exec_program(AstNode* root);

int main(void) {
  /* Initialise symbol table (used by semantic, tac, and exec passes) */
  symtab_init();
  functab_init();

  /* ---- PARSE ---- */
  int parse_ok = (yyparse() == 0);
  AstNode* root = g_parse_result;

  if (!parse_ok) {
    fprintf(stderr, "Parsing failed.\n");
    ast_list_free(root);
    symtab_free();
    return 1;
  }

  /* ---- SEMANTIC CHECK ---- */
  int sem_errs = semantic_check(root);
  if (sem_errs > 0) {
    fprintf(stderr, "Parsing OK, but semantic errors: %d\n", sem_errs);
    ast_list_free(root);
    symtab_free();
    return 2;
  }

  /* ---- TAC GENERATION ---- */
  tac_generate(root);

  /* ---- EXECUTION ---- */
  exec_program(root);

  /* ---- CLEANUP ---- */
  ast_list_free(root);
  symtab_free();
  functab_free();

  printf("Parsing + Semantic OK.\n");
  return 0;
}
