# EngBang Categorized Test Suite

This pack is organized by feature so you can run one area at a time.

## Success tests

- `success/basic/initializations_test.txt`
- `success/basic/expressions_test.txt`
- `success/basic/update_and_cast_test.txt`
- `success/conditions/conditions_test.txt`
- `success/conditions/nested_conditions_test.txt`
- `success/loops/loop_test.txt`
- `success/loops/custom_step_loop_test.txt`
- `success/functions/functions_test.txt`
- `success/functions/function_logic_test.txt`
- `success/combined/full_program_test.txt`

## Error tests

- `errors/basic/basic_errors_test.txt`
- `errors/conditions/condition_errors_test.txt`
- `errors/loops/loop_errors_test.txt`
- `errors/functions/function_errors_test.txt`
- `errors/syntax/missing_pipe_error_test.txt`
- `errors/syntax/invalid_keyword_error_test.txt`
- `errors/syntax/invalid_comparator_style_error_test.txt`

## Run one file in PowerShell

```powershell
Get-Content .\success\basic\initializations_test.txt | .\compiler.exe
```

## Notes

- All success files are written to match the **current implemented grammar** in the updated project.
- Condition tests use comparator-only condition items (`{==}`, `{!=}`, `{>=}`, `{<=}`, `{>}`, `{<}`) and `{}` skip.
- Custom loop-step tests cover `poriborton_by` with `+`, `*`, `/`, and float stepping.
- Syntax-error tests are kept separate because parsing normally stops at the first syntax error.
