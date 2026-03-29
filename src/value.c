/* value.c — Typed runtime value helpers and casting helpers */
#include "value.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ================================================================
   Type utilities
   ================================================================ */
const char* type_name(Type t) {
  switch (t) {
    case T_INT:   return "shonkha";
    case T_FLOAT: return "doshomik";
    case T_STR:   return "lekha";
    case T_BOOL:  return "shotto";
    default:      return "unknown";
  }
}

/* ================================================================
   EvalVal constructors
   ================================================================ */
EvalVal eval_int(long i) {
  EvalVal e;
  e.type = T_INT;
  e.val.i = i;
  e.owns_str = 0;
  return e;
}

EvalVal eval_float(double f) {
  EvalVal e;
  e.type = T_FLOAT;
  e.val.f = f;
  e.owns_str = 0;
  return e;
}

EvalVal eval_bool(int b) {
  EvalVal e;
  e.type = T_BOOL;
  e.val.b = b;
  e.owns_str = 0;
  return e;
}

/* Copies s into a fresh heap allocation. */
EvalVal eval_str_copy(const char* s) {
  EvalVal e;
  e.type = T_STR;
  e.val.s = strdup(s ? s : "");
  e.owns_str = 1;
  return e;
}

/* Takes ownership of the already-malloc'd string s. */
EvalVal eval_str_own(char* s) {
  EvalVal e;
  e.type = T_STR;
  e.val.s = s;
  e.owns_str = 1;
  return e;
}

EvalVal eval_unknown(void) {
  EvalVal e;
  e.type = T_UNKNOWN;
  e.val.i = 0;
  e.owns_str = 0;
  return e;
}

/* ================================================================
   Free an EvalVal's owned string (no-op if not owned or not STR).
   ================================================================ */
void eval_free(EvalVal* v) {
  if (!v) return;
  if (v->type == T_STR && v->owns_str && v->val.s) {
    free(v->val.s);
    v->val.s = NULL;
  }
  v->owns_str = 0;
}

/* ================================================================
   cast_value — convert EvalVal in to target type.
   Returns 1 on success, 0 on unsupported conversion.
   ================================================================ */
int cast_value(const EvalVal* in, Type target, EvalVal* out) {
  if (!in || !out) return 0;
  out->type = target;
  out->owns_str = 0;

  switch (target) {
    case T_INT:
      if (in->type == T_INT)   { out->val.i = in->val.i;              return 1; }
      if (in->type == T_FLOAT) { out->val.i = (long)in->val.f;        return 1; }
      if (in->type == T_BOOL)  { out->val.i = (long)in->val.b;        return 1; }
      if (in->type == T_STR) {
        char* end = NULL;
        long x = strtol(in->val.s ? in->val.s : "", &end, 10);
        if (!end || *end != '\0') return 0;
        out->val.i = x;
        return 1;
      }
      return 0;

    case T_FLOAT:
      if (in->type == T_FLOAT) { out->val.f = in->val.f;              return 1; }
      if (in->type == T_INT)   { out->val.f = (double)in->val.i;      return 1; }
      if (in->type == T_BOOL)  { out->val.f = (double)in->val.b;      return 1; }
      if (in->type == T_STR) {
        char* end = NULL;
        double x = strtod(in->val.s ? in->val.s : "", &end);
        if (!end || *end != '\0') return 0;
        out->val.f = x;
        return 1;
      }
      return 0;

    case T_BOOL:
      if (in->type == T_BOOL)  { out->val.b = in->val.b;              return 1; }
      if (in->type == T_INT)   { out->val.b = (in->val.i != 0);       return 1; }
      if (in->type == T_FLOAT) { out->val.b = (in->val.f != 0.0);     return 1; }
      return 0;

    case T_STR: {
      char buf[128];
      if (in->type == T_STR) {
        out->val.s = strdup(in->val.s ? in->val.s : "");
      } else if (in->type == T_INT) {
        snprintf(buf, sizeof(buf), "%ld", in->val.i);
        out->val.s = strdup(buf);
      } else if (in->type == T_FLOAT) {
        snprintf(buf, sizeof(buf), "%.6g", in->val.f);
        out->val.s = strdup(buf);
      } else if (in->type == T_BOOL) {
        snprintf(buf, sizeof(buf), "%d", in->val.b ? 1 : 0);
        out->val.s = strdup(buf);
      } else {
        return 0;
      }
      out->owns_str = 1;
      return 1;
    }

    default:
      return 0;
  }
}
