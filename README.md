# EngBang Compiler

A modular compiler for **EngBang** — a Bengali-inspired programming language — built with Flex, Bison, and C.

## Architecture

The compiler is split into five clean, independent passes that operate on a shared AST:

```
yyparse()           →  AST (parser.y + lexer.l + ast.c)
semantic_check()    →  Type validation, symtab population  (semantic.c)
tac_generate()      →  Three-Address Code to stdout        (tac.c)
exec_program()      →  AST interpreter / runtime           (exec.c)
```

---

## Project Structure

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
│   ├── main.c        # Entry point — orchestrates the four passes
│   ├── lexer.l       # Flex lexer
│   ├── parser.y      # Bison grammar — builds AST ONLY (no semantics/eval)
│   ├── ast.c         # AST node constructors and recursive cleanup
│   ├── value.c       # Typed runtime value helpers and cast_value()
│   ├── symtab.c      # Symbol table (linked list)
│   ├── functab.c     # Function table (registration, lookup, param storage)
│   ├── semantic.c    # Semantic analysis — type checking, symtab population
│   ├── tac.c         # TAC generation from AST
│   └── exec.c        # AST interpreter — runtime execution
├── tests/            # Test input files (.txt) and PowerShell test scripts
├── outputs/          # Reference output files
├── Makefile
└── README.md
```

### Separation of concerns

| File | Responsibility | Must NOT |
|------|---------------|----------|
| `parser.y` | Build AST nodes | Call symtab / emit TAC / eval expressions |
| `semantic.c` | Type check, populate symtab | Execute code / emit TAC |
| `tac.c` | Emit TAC from the validated AST | Modify symtab / execute code |
| `exec.c` | Interpret the AST at runtime | Emit TAC |

---

## Build

### Prerequisites

- [MinGW GCC](https://www.mingw-w64.org/) — `gcc`
- [GNU Bison 2.x+](https://www.gnu.org/software/bison/) — `bison`
- [Flex](https://github.com/westes/flex) — `flex`

### Using Make (recommended)

```sh
mingw32-make
```

### Manual Build

```powershell
# Step 1 – generate parser
bison -d src/parser.y          # produces src/parser.tab.c + src/parser.tab.h

# Step 2 – generate lexer
flex src/lexer.l               # produces src/lex.yy.c

# Step 3 – compile everything
gcc -I include/ -Wall -o compiler.exe `
    src/parser.tab.c src/lex.yy.c `
    src/main.c src/ast.c src/value.c src/symtab.c src/functab.c `
    src/semantic.c src/tac.c src/exec.c
```

### Clean

```sh
mingw32-make clean
```

---

## Run

```powershell
Get-Content tests/test_01_variables.txt | .\compiler.exe
```

The compiler outputs:
1. TAC lines prefixed with `TAC:` (three-address code)
2. Program output (from `bolo` statements)
3. Final status line `Parsing + Semantic OK.`

### Exit codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | Parse error |
| 2 | Semantic errors |

---

## Test

```powershell
# Run a single test file:
Get-Content tests\test_13_combined.txt | .\compiler.exe

# Run the full test suite (26 tests — success + error):
powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1
```

Or via Make:
```sh
mingw32-make test
```

### Test file index

| File | What it tests |
|------|---------------|
| `test_01_variables.txt` | Declarations — all four types |
| `test_02_constants_cast.txt` | `pakka`, `khaali`, `banaw` |
| `test_03_arithmetic.txt` | `+` `-` `*` `/` expressions |
| `test_04_update.txt` | `bodlao` variable update |
| `test_05_conditional_if.txt` | If-only conditional |
| `test_06_conditional_ifelse.txt` | If / else |
| `test_07_conditional_multi.txt` | Multiple OR-condition groups |
| `test_08_loop_inc.txt` | Loop with `barbe` (increment) |
| `test_09_loop_dec.txt` | Loop with `komabe` (decrement) |
| `test_10_loop_newvar.txt` | Loop with inline variable declaration |
| `test_11_functions.txt` | Function definition and call |
| `test_12_functions_forward.txt` | Forward function calls |
| `test_13_combined.txt` | All features combined |
| `err_01_undeclared.txt` | Undeclared variable |
| `err_02_redeclaration.txt` | Redeclaration |
| `err_03_type_mismatch_decl.txt` | Type mismatch in declaration |
| `err_04_type_mismatch_update.txt` | Type mismatch in update |
| `err_05_const_update.txt` | Update of constant |
| `err_06_cast_mismatch.txt` | Cast / declared type mismatch |
| `err_07_cond_undeclared.txt` | Undeclared var in conditional |
| `err_08_cond_type_mismatch.txt` | Type mismatch in conditional |
| `err_09_return_type.txt` | Return type mismatch in function |
| `err_10_loop_end_var.txt` | Loop end variable name mismatch |
| `err_11_loop_ctrl_var.txt` | Loop control variable mismatch |
| `err_12_syntax_pipe.txt` | Missing pipe `\|` terminator |
| `err_13_syntax_keyword.txt` | Unknown keyword |

---

## Language Reference

### Types

| Keyword    | Type    |
|------------|---------|
| `shonkha`  | Integer |
| `doshomik` | Float   |
| `lekha`    | String  |
| `shotto`   | Boolean |

### Keywords

| Keyword  | Purpose                  |
|----------|--------------------------|
| `rakho`  | Declare variable         |
| `pakka`  | Declare constant         |
| `khaali` | Uninitialized declaration|
| `bodlao` | Update variable          |
| `banaw`  | Type cast                |
| `bolo`   | Print                    |
| `ferao`  | Return from function     |
| `barbe`  | Loop increment           |
| `komabe` | Loop decrement           |
| `thamo`  | Loop break               |

### Examples

**Variable Declaration**
```
10 rakho x -> shonkha |
3.14 rakho pi -> doshomik |
"Hello" rakho msg -> lekha |
```

**Print**
```
bolo x |
bolo "Hello World" |
```

**Conditional**
```
x -> 10 {
  [{==}] {
    bolo "x is 10" |
  }
}
[] {
  bolo "x is not 10" |
}
|
```

**Loop**
```
[i -> 0 -> shonkha, i -> 5] {
  bolo i |
  i barbe
}
```

**Function**
```
add(x -> shonkha, y -> shonkha) -> shonkha {
  ferao x + y |
}
```

**Type Cast**
```
5 banaw doshomik rakho y -> doshomik |
```
