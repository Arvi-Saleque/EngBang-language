# EngBang Compiler — Change Log

## Feature: Custom Loop Step (`poriborton_by`)

### Problem
The old loop syntax only supported fixed steps:
- `barbe`  → always `i += 1`
- `komabe` → always `i -= 1`
- `thamo`  → run body once

There was no way to write `i += 10`, `i *= 5`, `i /= 2`, etc.

### Solution
A new keyword `poriborton_by` (Bengali: "change by") with the syntax:

```
var_name poriborton_by OP amount
```

| Example                   | Meaning      |
|---------------------------|--------------|
| `x poriborton_by +5`      | `x = x + 5`  |
| `x poriborton_by -2`      | `x = x - 2`  |
| `x poriborton_by *10`     | `x = x * 10` |
| `x poriborton_by /4`      | `x = x / 4`  |

The `amount` can be an integer or float literal. `+` and `*` operators use `<=` as the loop-continue condition (ascending); `-` and `/` use `>=` (descending).

---

## Files Modified

### `include/ast.h`
- Added `LOOP_CUSTOM` to the `LoopStep` enum.
- Added two new fields to `LoopData`:
  - `char step_op`   — stores the operator character (`+`, `-`, `*`, `/`).
  - `AstExpr* step_expr` — owns the step amount expression.
- Updated `ast_stmt_loop` declaration to accept `char step_op` and `AstExpr* step_expr`.

### `src/ast.c`
- Updated `ast_stmt_loop` implementation to store `step_op` and `step_expr`.
- Updated `ast_list_free` (`STMT_LOOP` branch) to call `ast_expr_free` on `step_expr` to prevent memory leaks.

### `src/lexer.l`
- Added rule: `"poriborton_by" { return KW_PORIBORTON_BY; }`

### `src/parser.y`
- Added `LoopStepData` struct (`{ char step_op; AstExpr* step_expr; }`) to `%code requires`.
- Extended `LoopCtrlData` struct with `char step_op` and `AstExpr* step_expr` fields.
- Added `LoopStepData lstep` to the `%union`.
- Added `%token KW_PORIBORTON_BY`.
- Added `%type <lstep> loop_step` declaration.
- Updated existing `loop_ctrl` alternatives for `barbe`, `komabe`, `thamo` to zero-initialise the new fields.
- Added new `loop_ctrl` alternative: `ID KW_PORIBORTON_BY loop_step`.
- Added new `loop_step` non-terminal with 10 rules covering all combinations of operator (`PLUS`, `MINUS`, `STAR`, `SLASH`, or bare `INT`/`FLOAT` with embedded sign) and literal type (`INT` / `FLOAT`).
- Updated the `loop_stmt` action to forward `step_op` and `step_expr` to `ast_stmt_loop`.

### `src/semantic.c`
- In the `STMT_LOOP` case, added a check for `LOOP_CUSTOM`: validates that the `step_expr` type matches the loop variable's type (with the usual INT→FLOAT widening allowance).

### `src/exec.c`
- Updated the loop condition check to handle `LOOP_CUSTOM`:  `+`/`*` operators → ascending condition (`var <= end`); `-`/`/` operators → descending condition (`var >= end`).
- Replaced the hardcoded `+1`/`-1` advance block with a switch over `step_op` that applies the correct arithmetic operation (`+`, `-`, `*`, `/`) using the evaluated `step_expr`.

### `src/tac.c`
- Updated the TAC loop condition branch to handle `LOOP_CUSTOM` (same ascending/descending logic as exec.c).
- Updated the TAC step-advance emit to output `var = var OP amount` for `LOOP_CUSTOM` instead of the hardcoded `+1`/`-1`.

---

## New Files

### `tests/test_14_loop_custom_step.txt`
A test covering three `poriborton_by` loops:
1. `+10` step — accumulates a sum.
2. `*2`  step — doubles the counter each iteration.
3. `/2`  step — halves the counter each iteration (descending).
