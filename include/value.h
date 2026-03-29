// value.h — Typed runtime value helpers and casting helpers
#ifndef VALUE_H
#define VALUE_H

/* ===== Type enum (shared across all modules) ===== */
typedef enum {
  T_INT,
  T_FLOAT,
  T_STR,
  T_BOOL,
  T_UNKNOWN
} Type;

/* ===== Raw value store ===== */
typedef union {
  long   i;
  double f;
  char*  s;
  int    b;
} Value;

/* ===== Typed runtime value ===== */
typedef struct {
  Type  type;
  Value val;
  int   owns_str;   /* 1 = val.s was malloc'd and must be freed by caller */
} EvalVal;

/* ===== Type utilities ===== */
const char* type_name(Type t);

/* ===== EvalVal constructors ===== */
EvalVal eval_int(long i);
EvalVal eval_float(double f);
EvalVal eval_bool(int b);
EvalVal eval_str_copy(const char* s);  /* copies s into a new allocation */
EvalVal eval_str_own(char* s);         /* takes ownership of already-malloc'd s */
EvalVal eval_unknown(void);

/* Free an EvalVal's owned string (if any) */
void eval_free(EvalVal* v);

/* Cast in to target type, writing result to *out.
   Returns 1 on success, 0 if the conversion is not supported. */
int cast_value(const EvalVal* in, Type target, EvalVal* out);

#endif /* VALUE_H */
