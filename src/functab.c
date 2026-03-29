/* functab.c — Function definition table implementation */
#include "functab.h"
#include <stdlib.h>
#include <string.h>

static FuncDef* g_func_head = NULL;

void functab_init(void) { g_func_head = NULL; }

void functab_free(void) {
  FuncDef* f = g_func_head;
  while (f) {
    FuncDef* next = f->next;
    free(f->name);
    for (int i = 0; i < f->param_count; i++) free(f->params[i].name);
    free(f->params);
    /* f->body is owned by the AST — not freed here */
    free(f);
    f = next;
  }
  g_func_head = NULL;
}

int functab_register(const char* name, Type ret_type,
                      FuncParamNode* params, int count, AstNode* body) {
  if (functab_lookup(name)) return 0;   /* redefinition */
  FuncDef* f = (FuncDef*)calloc(1, sizeof(FuncDef));
  f->name        = strdup(name);
  f->return_type = ret_type;
  f->params      = params;   /* takes ownership */
  f->param_count = count;
  f->body        = body;
  f->next        = g_func_head;
  g_func_head    = f;
  return 1;
}

FuncDef* functab_lookup(const char* name) {
  for (FuncDef* f = g_func_head; f; f = f->next)
    if (strcmp(f->name, name) == 0) return f;
  return NULL;
}
