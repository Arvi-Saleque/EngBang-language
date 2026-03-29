// symtab.h — Symbol table: declaration, lookup, value storage
#ifndef SYMTAB_H
#define SYMTAB_H

#include "value.h"   /* Type, Value */

typedef struct Symbol {
  char*          name;
  Type           type;
  int            is_const;      /* 1 if declared with pakka */
  int            initialized;   /* 1 if a value was declared */
  int            decl_line;
  struct Symbol* next;
  Value          val;
} Symbol;

void    symtab_init(void);
void    symtab_free(void);

Symbol* symtab_lookup(const char* name);

/* Returns 1 on success, 0 on redeclaration */
int     symtab_declare(const char* name, Type type, int is_const,
                        int initialized, int decl_line);

/* Returns 1 on success, 0 if not found, -1 on type mismatch */
int     symtab_set_value(const char* name, Type t, Value v);

/* Returns 1 on success, 0 if not found */
int     symtab_get_value(const char* name, Value* out);

/* Scope support for function calls:
   push_scope() saves the current top-of-stack position.
   pop_scope()  frees all symbols declared since the last push.
   Local variables shadow globals; lookup searches from newest outward. */
void    symtab_push_scope(void);
void    symtab_pop_scope(void);

#endif /* SYMTAB_H */
