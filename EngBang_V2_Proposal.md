# EngBang Programming Language — V2

**Date:** 01 – 26 – 2026

---

**Salek Bin Hossain**
Roll: 2107026
Lab Group: A1

---

## 1. Objectives

- Design a unique programming language syntax (**EngBang**) using Banglish-style keywords.
- Define strict rules for variable declaration, updates, constants, default initialization, and type casting.
- Support arithmetic expressions (`+`, `–`, `*`, `/`) with proper operator precedence.
- Define a unified conditional system where all condition operators/operations are written using `{ }` and condition lists use `[ ]`.
- Support Python-like chained comparisons (e.g., `10 <= x <= 20`, `a == b == c`) using EngBang bindings.
- Define a loop construct using bracket-based headers with increment (`barbe`), decrement (`komabe`), and execute-once (`thamo`) control keywords.
- Support user-defined functions with typed parameters, return values (`ferao`), and forward calls.
- Build a full compiler pipeline: lexer → parser → AST → semantic check → TAC generation → interpreter.
- Document corner cases so the language remains unambiguous and parser-friendly.

---

## 2. Introduction

**EngBang v2** is designed to avoid the typical C/Python look and feel. Instead of placing operators directly inside conditions, EngBang evaluates conditions using a **binding-first model**: `var -> value` declares what is being compared, and a unified `{ }` condition token decides how the comparison is performed. Logical composition is handled using lists: a single `[ ... ]` represents AND across bindings, and multiple lists represent OR. The language also features a consistent bracket-based loop syntax and typed function definitions that reinforce the same "explicit, verbose" philosophy throughout.

The EngBang v2 compiler is implemented as a **four-pass pipeline** in C using Flex and Bison:

```
Source Code
    │
    ▼
[Lexer (lexer.l)]  ──────────────►  Token stream
    │
    ▼
[Parser (parser.y)]  ────────────►  Abstract Syntax Tree (AST)
    │
    ▼
[Semantic Checker (semantic.c)]  ►  Type-validated AST + Symbol Table
    │
    ▼
[TAC Generator (tac.c)]  ────────►  Three-Address Code (stdout)
    │
    ▼
[Interpreter (exec.c)]  ─────────►  Program Output (stdout)
```

---

## 3. Language Specification: Part 1 — Variables

### 3.1 Data Types

| Type       | Meaning      | Valid Values (Examples)         |
|------------|--------------|----------------------------------|
| `shonkha`  | Integer      | `-5`, `0`, `10`, `999`          |
| `doshomik` | Float        | `3.14`, `-0.50`, `10.0`         |
| `lekha`    | Text/String  | `"hello"`, `"Talha \"Safin\""` |
| `shotto`   | Boolean      | `0` or `1` only                 |

**Boolean convention:** `shotto` values are strictly `0` (false) and `1` (true).

---

### 3.2 Identifiers (Variable Names)

**Rules:**
- Must start with `A–Z`, `a–z`, or underscore `_`.
- May contain `A–Z`, `a–z`, `0–9`, `_` after the first character.
- Reserved words cannot be used as identifiers.

**Complete reserved words list:**

```
rakho   bodlao  pakka   khaali  ar      bolo
banaw   barbe   komabe  thamo   ferao
->      |       []      {}      [ ]     { }
```

**Examples:**

```
# Valid
10 rakho x -> shonkha |
khaali rakho _temp -> doshomik |
"hi" rakho user_name -> lekha |

# Invalid
10 rakho 1x -> shonkha |    # starts with digit
10 rakho rakho -> shonkha | # reserved word
```

---

### 3.3 Statement Termination

**Rule:** Every regular statement ends with `|`.

```
bolo "Hello" |
10 bodlao x |
```

**Exception — Block statements:** Loop definitions and function definitions end with a closing `}` and do **not** use a trailing `|`.

```
# Loop — no | after closing }
[i -> 1, i -> 5] {
  bolo i |
  i barbe
}

# Function — no | after closing }
add(x -> shonkha, y -> shonkha) -> shonkha {
  ferao x + y |
}
```

**Conditional chains end with `|`** (after the final closing `}`):

```
x -> 10 {
  [{==}] { bolo "ten" | }
}
[] { bolo "other" | }
|
```

---

### 3.4 Declaration (`rakho`)

```
value rakho var_name -> type |
```

**Rules:**
- `rakho` declares a new variable and initializes it.
- Redeclaration of the same name is not allowed (`bodlao` is used to change values).

```
# Valid
10 rakho x -> shonkha |
"Talha" rakho name -> lekha |

# Invalid (redeclaration)
10 rakho x -> shonkha |
20 rakho x -> shonkha |   # ERROR
```

---

### 3.5 Multiple Declarations in One Line (comma-free)

Use `ar` to chain declarations; end the line with one `|`.

```
10 rakho x -> shonkha ar 20 rakho y -> shonkha ar "hi" rakho s -> lekha |
```

---

### 3.6 Default Values (`khaali`)

```
khaali rakho var_name -> type |
```

**Default mapping:**

| Type       | Default Value |
|------------|---------------|
| `shonkha`  | `0`           |
| `doshomik` | `0.0`         |
| `lekha`    | `""`          |
| `shotto`   | `0`           |

```
khaali rakho count -> shonkha |
khaali rakho avg   -> doshomik |
khaali rakho title -> lekha |
khaali rakho flag  -> shotto |
```

---

### 3.7 Update (`bodlao`)

```
value bodlao var_name |
```

**Rules:**
- Variable must be declared before update.
- Type mismatch is an error (strict typing).
- `pakka` (constant) variables cannot be updated.

```
# Valid
10 rakho x -> shonkha |
20 bodlao x |

# Invalid: undeclared
20 bodlao y |        # ERROR

# Invalid: type mismatch
10 rakho x -> shonkha |
"hi" bodlao x |      # ERROR
```

---

### 3.8 Constants (`pakka`)

```
value pakka rakho NAME -> type |
```

**Rules:**
- `pakka` variables cannot be updated with `bodlao`.
- Constants must be initialized (explicit value or `khaali`).

```
10 pakka rakho LIMIT   -> shonkha |
"v2" pakka rakho VERSION -> lekha |
khaali pakka rakho FLAG  -> shotto |

20 bodlao LIMIT |    # ERROR: cannot update pakka
```

---

### 3.9 Type Casting (`banaw`)

```
value banaw castType rakho var_name -> type |    # cast + declare
value banaw castType bodlao var_name |           # cast + update
```

The expression `value` is first converted to `castType`, then stored.

```
"123"  banaw shonkha  rakho n -> shonkha |
"3.50" banaw doshomik rakho f -> doshomik |
123    banaw lekha    rakho s -> lekha |
"999"  banaw shonkha  bodlao n |
```

---

### 3.10 Arithmetic Expressions

EngBang supports four arithmetic operators inside expressions. These can be used anywhere a value is expected: in declarations, updates, print statements, function arguments, and conditional bindings.

| Operator | Meaning        |
|----------|----------------|
| `+`      | Addition       |
| `-`      | Subtraction    |
| `*`      | Multiplication |
| `/`      | Division       |

**Operator precedence:** `*` and `/` bind tighter than `+` and `-` (same as standard mathematics).  
**Parentheses** `( )` can be used to override precedence.

```
10 rakho a -> shonkha |
3  rakho b -> shonkha |

bolo a + b |       # 13
bolo a - b |       # 7
bolo a * b |       # 30
bolo a / b |       # 3

bolo (a + b) * 2 | # 26
```

**Arithmetic in declarations and updates:**

```
5 rakho x -> shonkha |
x * 2 bodlao x |          # x is now 10
x + 3 rakho y -> shonkha | # y = 13
```

**Type rules for arithmetic:**
- `shonkha OP shonkha` → result is `shonkha`.
- If either operand is `doshomik`, result is `doshomik`.
- Arithmetic on `lekha` or `shotto` operands is a semantic error.

---

## 4. Language Specification: Part 2 — Conditionals (IF / ELSEIF / ELSE)

EngBang conditionals use a binding-first model with unified `{ }` condition items and `[ ]` groups.

### 4.1 IF / ELSEIF / ELSE Format

```
# IF
<bindings> {
  <groups> {
    <statements>    # each ends with |
  }
}

# ELSEIF (optional, can repeat)
<bindings> {
  <groups> {
    <statements> |
  }
}

# ELSE (optional)
[] {
  <statements> |
}
|
```

The entire conditional chain (from the first `<bindings>` to the final `}`) is terminated with a single `|`.

---

### 4.2 Bindings

```
var -> value ar var -> value ar ...
```

- Binding order matters: condition items apply in the same order.
- Value may be a literal, an identifier, or an arithmetic expression.
- The same variable may appear multiple times in bindings (e.g., `x -> 10 ar x -> 20`).

---

### 4.3 AND / OR with `[ ]` Groups

- **One** `[ ... ]` is AND across all bindings.
- **Multiple** `[ ... ][ ... ]` groups are OR: the first matching group runs the body.
- `[]` (empty brackets with no content) is reserved exclusively for the **ELSE** branch.

```
a -> 10 ar b -> 0 {
  [{>=}, {% 2}][{==}, {}] {
    bolo "OK" |
  }
}
[] { bolo "NO" | }
|
```

---

### 4.4 Strict Count Matching

The number of condition items in each `[ ]` group **must exactly equal** the number of bindings.

```
# bindings = 3 ✓
a -> 1 ar b -> 2 ar c -> 3 {
  [{==}, {}, {>=}] { bolo "valid" | }
}
|

# Invalid — count mismatch ✗
a -> 1 ar b -> 2 ar c -> 3 {
  [{==}, {>=}] { bolo "ERROR" | }   # only 2 items for 3 bindings
}
|
```

---

### 4.5 Condition Item Types

**A) Comparator-only:** `{==}` `{!=}` `{>=}` `{<=}` `{>}` `{<}`

Compares the variable directly against its bound value.

```
x -> 10 {
  [{>=}] { bolo "x >= 10" | }
}
|
```

**B) Transform-then-equality:** `{% 2}`, `{^ 5}`, `{+ 10}`, `{>> 1}`, etc.

Means `(var OP k) == bound_value`. The variable is transformed first, then checked for equality with the bound value.

```
x -> 0 {
  [{% 2}] { bolo "even" | }   # x % 2 == 0
}
|

x -> 10 {
  [{^ 5}] { bolo "match" | }  # x ^ 5 == 10
}
|
```

**C) Skip:** `{}` — Ignores this binding entirely in the current AND group.

```
cgpa -> 3.75 ar attendance -> 80 ar hasQuota -> 1 {
  [{>=}, {>=}, {}] { bolo "needs only cgpa+attendance" | }
}
|
```

---

### 4.6 Execution Order

1. Evaluate the **IF block** first: test OR-groups left to right; the first true group executes its body.
2. If IF fails, evaluate each **ELSEIF block** in order.
3. If none match, run the **ELSE block** (`[] { ... }`) if present.
4. Only one branch ever executes.

---

## 5. Language Specification: Part 3 — Loops

EngBang uses a bracket-based loop header. There is no `while` or `for` keyword; the loop is expressed entirely through the `[ ]` header and a control keyword at the end of the body.

### 5.1 Loop Syntax

```
[varName -> startVal, varName -> endVal] {
  <body statements>
  varName barbe        # increment control (no | here)
}
```

```
[varName -> startVal, varName -> endVal] {
  <body statements>
  varName komabe       # decrement control (no | here)
}
```

```
[varName -> startVal, varName -> endVal] {
  <body statements>
  thamo                # execute once and stop (no | here)
}
```

**Rules:**
- The variable name in the end slot (`varName -> endVal`) **must match** the variable name in the start slot.
- The loop header itself does **not** end with `|`; the loop is closed by `}`.
- All statements inside the loop body end with `|` as normal.
- The control keyword (`barbe`, `komabe`, or `thamo`) is the **last item** inside `{ }` and does **not** end with `|`.

---

### 5.2 Loop with Existing Variable (`barbe` / `komabe`)

When the variable is already declared, write the header without a type annotation:

```
[varName -> startVal, varName -> endVal] { ... varName barbe/komabe }
```

```
# Increment: prints 1, 2, 3, 4, 5
1 rakho i -> shonkha |

[i -> 1, i -> 5] {
  bolo i |
  i barbe
}

# Decrement: prints 5, 4, 3, 2, 1
5 rakho k -> shonkha |

[k -> 5, k -> 1] {
  bolo k |
  k komabe
}
```

---

### 5.3 Loop with Inline Variable Declaration

To declare the loop variable inside the header (no prior `rakho` needed), add `-> type` after the start value:

```
[varName -> startVal -> type, varName -> endVal] { ... varName barbe }
```

```
# Prints 0, 1, 2, 3, 4
[n -> 0 -> shonkha, n -> 4] {
  bolo n |
  n barbe
}
```

---

### 5.4 Loop Semantics

| Keyword  | Behaviour                                                              |
|----------|------------------------------------------------------------------------|
| `barbe`  | Increment: execute body, then `var++`. Continue while `var <= endVal`. |
| `komabe` | Decrement: execute body, then `var--`. Continue while `var >= endVal`. |
| `thamo`  | Execute body exactly once, then stop.                                  |

---

### 5.5 Loop Error Cases

```
# ERROR: end variable name must match init variable name
1 rakho i -> shonkha |

[i -> 1, j -> 5] {     # 'j' != 'i' → SEM_ERROR
  bolo i |
  i barbe
}
```

---

## 6. Language Specification: Part 4 — Functions

EngBang supports user-defined typed functions with parameters and a return value.

### 6.1 Function Definition

```
funcName(param1 -> type, param2 -> type, ...) -> returnType {
  <body statements>
}
```

- All parameters are typed using `->`.
- Multiple parameters are separated by `,`.
- The return type is specified after `->` following the closing `)`.
- The function body is enclosed in `{ }`.
- No `|` after the closing `}`.

```
add(x -> shonkha, y -> shonkha) -> shonkha {
  ferao x + y |
}

greet(name -> lekha) -> lekha {
  ferao name |
}
```

**Zero-parameter functions:**

```
hello() -> lekha {
  ferao "hi" |
}
```

---

### 6.2 Return Statement (`ferao`)

```
ferao expr |
```

- Every function must end with a `ferao` statement.
- The type of `expr` must match the declared return type.
- `ferao` is followed by the return expression and then `|`.

```
double(n -> shonkha) -> shonkha {
  ferao n * 2 |
}
```

---

### 6.3 Function Calls

Functions are called by placing arguments in parentheses. A call can appear anywhere an expression is valid.

```
funcName(arg1, arg2, ...)
```

```
bolo add(3, 7) |          # prints: 10
bolo double(6) |          # prints: 12

10 rakho result -> shonkha |
add(4, 6) bodlao result |  # result = 10
```

---

### 6.4 Forward Declarations (Call Before Definition)

EngBang supports calling a function before its definition appears in the source. The semantic pass performs a **pre-scan** of all function signatures before checking the rest of the program.

```
# Call appears before the function body — valid in EngBang
bolo double(6) |
bolo square(4) |

double(n -> shonkha) -> shonkha {
  ferao n * 2 |
}

square(n -> shonkha) -> shonkha {
  ferao n * n |
}
```

---

### 6.5 Scoping Rules

- Each function call pushes a new scope onto the symbol table.
- Parameters are declared as local variables in that scope.
- The scope is popped when the function returns.
- Outer variables are **not** accessible inside a function body (no closures).

---

## 7. Python-like Chained Comparisons

EngBang's binding-first model naturally supports Python-style chained comparisons by binding the same variable twice with different values.

```
# 10 <= x <= 20
x -> 10 ar x -> 20 {
  [{>=}, {<=}] { bolo "in range" | }
}
[] { bolo "out of range" | }
|

# a == b == c == d
a -> b ar b -> c ar c -> d {
  [{==}, {==}, {==}] { bolo "all equal" | }
}
[] { bolo "not equal" | }
|
```

---

## 8. C ↔ EngBang Examples

### Example 1: Even / Odd

**C:**
```c
if (x % 2 == 0) printf("jor\n");
else printf("bijor\n");
```

**EngBang:**
```
x -> 0 {
  [{% 2}] { bolo "jor" | }
}
[] { bolo "bijor" | }
|
```

---

### Example 2: Positive / Zero / Negative

**C:**
```c
if (n > 0) printf("positive\n");
else if (n == 0) printf("zero\n");
else printf("negative\n");
```

**EngBang:**
```
n -> 0 { [{>}]  { bolo "positive" | } }
n -> 0 { [{==}] { bolo "zero"     | } }
[] { bolo "negative" | }
|
```

---

### Example 3: Scholarship (AND + OR + Skip)

**C:**
```c
if ((cgpa >= 3.75 && attendance >= 80) || hasQuota == 1)
    printf("Eligible\n");
else
    printf("Not eligible\n");
```

**EngBang:**
```
cgpa -> 3.75 ar attendance -> 80 ar hasQuota -> 1 {
  [{>=}, {>=}, {}][{}, {}, {==}] { bolo "Eligible" | }
}
[] { bolo "Not eligible" | }
|
```

---

### Example 4: Grade Range

**C:**
```c
if (mark >= 80 && mark <= 100) printf("A+\n");
else printf("Not A+\n");
```

**EngBang:**
```
mark -> 80 ar mark -> 100 {
  [{>=}, {<=}] { bolo "A+" | }
}
[] { bolo "Not A+" | }
|
```

---

### Example 5: Boolean (`shotto` as 0/1)

**C:**
```c
if (!flag) printf("FALSE branch\n");
else printf("TRUE branch\n");
```

**EngBang:**
```
flag -> 0 { [{==}] { bolo "FALSE branch" | } }
[] { bolo "TRUE branch" | }
|
```

---

### Example 6: Loop — Sum 1 to N

**C:**
```c
int sum = 0;
for (int i = 1; i <= 5; i++) sum += i;
printf("%d\n", sum);
```

**EngBang:**
```
0 rakho sum -> shonkha |

[i -> 1 -> shonkha, i -> 5] {
  sum + i bodlao sum |
  i barbe
}

bolo sum |
```

---

### Example 7: Function — Recursive Absolute Value

**C:**
```c
int negate(int x) { return 0 - x; }
```

**EngBang:**
```
negate(x -> shonkha) -> shonkha {
  ferao 0 - x |
}

bolo negate(8) |    # prints: -8
```

---

### Example 8: Combined — Forward Call + Loop + Conditional

```
// Forward function call (add defined below)
bolo add(10, 5) |

// Accumulate 1 + 2 + 3 + 4 = 10
0 rakho total -> shonkha |

[i -> 1 -> shonkha, i -> 4] {
  total + i bodlao total |
  i barbe
}

bolo total |

// Check result
total -> 10 {
  [{==}] { bolo "total is 10" | }
}
[] { bolo "total is not 10" | }
|

// Function definition (after use — forward call is valid)
add(x -> shonkha, y -> shonkha) -> shonkha {
  ferao x + y |
}
```

---

## 9. Compiler Architecture

The EngBang v2 compiler is implemented in C using Flex (lexer) and Bison (parser) and structured as a strictly separated four-pass pipeline.

### 9.1 Project File Structure

```
projectr/
├── include/
│   ├── value.h       # Type, Value, EvalVal — shared runtime value types
│   ├── ast.h         # AST node definitions and constructors
│   ├── symtab.h      # Symbol table interface (declaration, lookup, values)
│   ├── functab.h     # Function table interface (registration, lookup)
│   ├── semantic.h    # Semantic analysis pass interface
│   └── tac.h         # TAC generation pass interface
├── src/
│   ├── main.c        # Entry point — orchestrates all four passes
│   ├── lexer.l       # Flex lexer (tokenisation)
│   ├── parser.y      # Bison grammar — builds the AST only
│   ├── ast.c         # AST node constructors and recursive cleanup
│   ├── value.c       # Typed runtime value helpers and cast_value()
│   ├── symtab.c      # Symbol table (scoped linked list)
│   ├── functab.c     # Function table (registration and lookup)
│   ├── semantic.c    # Semantic analysis — type checking, symtab population
│   ├── tac.c         # TAC generation from the validated AST
│   └── exec.c        # AST interpreter — runtime execution
├── tests/            # Test input files (.txt) and PowerShell test runner
├── Makefile
└── README.md
```

### 9.2 Pass Responsibilities

| Pass | File | Responsibility | Must NOT |
|------|------|----------------|----------|
| Parse | `parser.y` + `lexer.l` | Build AST nodes only | Call symtab / emit TAC / eval |
| Semantic | `semantic.c` | Type check; populate symtab | Execute code / emit TAC |
| TAC | `tac.c` | Emit three-address code from validated AST | Modify symtab / execute code |
| Execute | `exec.c` | Interpret the AST at runtime | Emit TAC |

### 9.3 Build Instructions

**Prerequisites:** MinGW GCC, GNU Bison 2.x+, Flex

```powershell
# Using Make (recommended)
mingw32-make

# Manual build
bison -d src/parser.y
flex src/lexer.l
gcc -I include/ -Wall -o compiler.exe `
    src/parser.tab.c src/lex.yy.c `
    src/main.c src/ast.c src/value.c src/symtab.c src/functab.c `
    src/semantic.c src/tac.c src/exec.c
```

### 9.4 Running the Compiler

```powershell
Get-Content tests/test_01_variables.txt | .\compiler.exe
```

### 9.5 TAC Output Format

The TAC pass prints three-address instructions to stdout before execution:

```
TAC: t0 = 10
TAC: x = t0
TAC: t1 = 3
TAC: t2 = t0 + t1
TAC: print t2
TAC: if x >= 10 goto L0
TAC: goto L1
TAC: L0:
TAC: L1:
```

### 9.6 Error Reporting

The compiler reports two classes of errors:

| Class | Example | Reported by |
|-------|---------|-------------|
| Syntax error | Missing `|`, bad token | Bison (`parser.y`) |
| Semantic error | Undeclared variable, type mismatch, `pakka` update, condition count mismatch | `semantic.c` |

Errors include the source line number:
```
SEM_ERROR at line 4: Use of undeclared variable 'x'
SEM_ERROR at line 7: Cannot update pakka variable 'LIMIT'
SEM_ERROR at line 12: Condition group has 2 items but 3 bindings exist
```

---

## 10. Complete Keyword Reference

| Keyword    | Role                                                        |
|------------|-------------------------------------------------------------|
| `rakho`    | Declare and initialize a variable                           |
| `bodlao`   | Update (re-assign) an existing variable                     |
| `pakka`    | Mark a variable as a constant (immutable)                   |
| `khaali`   | Use the default value for a declaration                     |
| `ar`       | Chain multiple declarations on one line                     |
| `bolo`     | Print a value to stdout                                     |
| `banaw`    | Type-cast a value before declaring or updating              |
| `barbe`    | Loop control — increment variable each iteration            |
| `komabe`   | Loop control — decrement variable each iteration            |
| `thamo`    | Loop control — execute body once then stop                  |
| `ferao`    | Return a value from a function                              |
| `shonkha`  | Integer type keyword                                        |
| `doshomik` | Float type keyword                                          |
| `lekha`    | String type keyword                                         |
| `shotto`   | Boolean type keyword                                        |

---

*End of EngBang v2 Project Proposal*
