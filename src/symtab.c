// symtab.c — Symbol table: declaration, lookup, value read/write
#include "symtab.h"
#include <stdlib.h>
#include <string.h>

static Symbol* g_head = NULL;

void symtab_init(void) {
  g_head = NULL;
}

void symtab_free(void) {
  Symbol* cur = g_head;
  while (cur) {
    Symbol* nxt = cur->next;
    if (cur->type == T_STR && cur->val.s) free(cur->val.s);
    free(cur->name);
    free(cur);
    cur = nxt;
  }
  g_head = NULL;
}

Symbol* symtab_lookup(const char* name) {
  for (Symbol* cur = g_head; cur; cur = cur->next) {
    if (strcmp(cur->name, name) == 0) return cur;
  }
  return NULL;
}

int symtab_declare(const char* name, Type type, int is_const,
                    int initialized, int decl_line) {
  if (symtab_lookup(name)) return 0;   /* redeclaration */

  Symbol* s = (Symbol*)calloc(1, sizeof(Symbol));
  s->name        = strdup(name);
  s->type        = type;
  s->is_const    = is_const;
  s->initialized = initialized;
  s->decl_line   = decl_line;

  /* Initialise val to language-defined defaults */
  switch (type) {
    case T_INT:   s->val.i = 0;          break;
    case T_FLOAT: s->val.f = 0.0;        break;
    case T_BOOL:  s->val.b = 0;          break;
    case T_STR:   s->val.s = strdup(""); break;
    default: break;
  }

  s->next = g_head;
  g_head  = s;
  return 1;
}

int symtab_set_value(const char* name, Type t, Value v) {
  Symbol* s = symtab_lookup(name);
  if (!s) return 0;                          /* not found */
  if (t != T_UNKNOWN && s->type != t) return -1;  /* type mismatch */

  if (s->type == T_STR) {
    if (s->val.s) free(s->val.s);
    s->val.s = strdup(v.s ? v.s : "");
  } else {
    s->val = v;
  }
  s->initialized = 1;
  return 1;
}

int symtab_get_value(const char* name, Value* out) {
  Symbol* s = symtab_lookup(name);
  if (!s || !out) return 0;
  *out = s->val;   /* for strings: returns pointer owned by symtab — don't free it */
  return 1;
}

/* ================================================================
   SCOPE SUPPORT (for function calls)
   ================================================================ */
#define MAX_SCOPE_DEPTH 64
static Symbol* scope_markers[MAX_SCOPE_DEPTH];
static int     scope_depth = 0;

void symtab_push_scope(void) {
  if (scope_depth < MAX_SCOPE_DEPTH)
    scope_markers[scope_depth++] = g_head;
}

void symtab_pop_scope(void) {
  if (scope_depth == 0) return;
  Symbol* marker = scope_markers[--scope_depth];
  /* free all symbols declared since the last push */
  while (g_head != marker) {
    Symbol* s = g_head;
    g_head = s->next;
    if (s->type == T_STR && s->val.s) free(s->val.s);
    free(s->name);
    free(s);
  }
}
