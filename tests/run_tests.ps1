# EngBang Compiler — Test Suite
# Run from project root:
#   powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1

$compiler = ".\compiler.exe"
$testDir  = ".\tests"

# ---------------------------------------------------------------------------
# Test definitions
# ---------------------------------------------------------------------------

$success_tests = @(
    @{ file = "success\test_variables.txt";         expect = "all types, pakka, khaali" },
    @{ file = "success\test_cast.txt";              expect = "banaw cast" },
    @{ file = "success\test_arithmetic.txt";        expect = "int + float arithmetic" },
    @{ file = "success\test_update.txt";            expect = "bodlao updates" },
    @{ file = "success\test_expressions.txt";       expect = "precedence and parentheses" },
    @{ file = "success\test_conditions.txt";        expect = "if / else / OR / AND / nested" },
    @{ file = "success\test_loops.txt";             expect = "barbe / komabe / thamo / agao / nested" },
    @{ file = "success\test_custom_step_loops.txt"; expect = "poriborton_by +, *, /, float" },
    @{ file = "success\test_functions.txt";         expect = "forward calls / nested / logic" },
    @{ file = "success\test_combined.txt";          expect = "combined all features" }
)

$error_tests = @(
    @{ file = "errors\err_01_undeclared.txt";          expect = "undeclared variable" },
    @{ file = "errors\err_02_redeclaration.txt";       expect = "redeclaration" },
    @{ file = "errors\err_03_type_mismatch_decl.txt";  expect = "type mismatch in declaration" },
    @{ file = "errors\err_04_type_mismatch_update.txt";expect = "type mismatch in update" },
    @{ file = "errors\err_05_const_update.txt";        expect = "cannot update constant" },
    @{ file = "errors\err_06_cast_mismatch.txt";       expect = "cast type mismatch" },
    @{ file = "errors\err_07_cond_undeclared.txt";     expect = "undeclared in conditional" },
    @{ file = "errors\err_08_cond_type_mismatch.txt";  expect = "type mismatch in conditional" },
    @{ file = "errors\err_09_cond_group_mismatch.txt"; expect = "group count mismatch" },
    @{ file = "errors\err_10_return_type.txt";         expect = "return type mismatch" },
    @{ file = "errors\err_11_func_arg_count.txt";      expect = "wrong argument count" },
    @{ file = "errors\err_12_func_arg_type.txt";       expect = "argument type mismatch" },
    @{ file = "errors\err_13_func_undefined.txt";      expect = "undefined function" },
    @{ file = "errors\err_14_loop_end_var.txt";        expect = "loop end variable mismatch" },
    @{ file = "errors\err_15_loop_ctrl_var.txt";       expect = "loop control variable mismatch" },
    @{ file = "errors\err_16_loop_step_type.txt";      expect = "step type mismatch" },
    @{ file = "errors\err_17_syntax_pipe.txt";         expect = "syntax error (missing pipe)" },
    @{ file = "errors\err_18_syntax_keyword.txt";      expect = "syntax error (bad keyword)" },
    @{ file = "errors\err_19_syntax_comparator.txt";   expect = "syntax error (direct comparator)" }
)

# ---------------------------------------------------------------------------
# Runner
# ---------------------------------------------------------------------------

$passed = 0
$failed = 0

function Run-Test($file, $expectPass) {
    $path   = Join-Path $testDir $file
    $output = Get-Content $path | & $compiler 2>&1
    $exit   = $LASTEXITCODE
    $ok     = if ($expectPass) { $exit -eq 0 } else { $exit -ne 0 }
    return @{ ok = $ok; exit = $exit; output = ($output -join "`n") }
}

Write-Host ""
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   EngBang Compiler  —  Test Suite"        -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# — Success tests
Write-Host ""
Write-Host "  SUCCESS TESTS  (expect exit 0)" -ForegroundColor Green
Write-Host "  --------------------------------" -ForegroundColor Green

foreach ($t in $success_tests) {
    $r = Run-Test $t.file $true
    if ($r.ok) {
        Write-Host ("  PASS  " + $t.file) -ForegroundColor Green
        $passed++
    } else {
        Write-Host ("  FAIL  " + $t.file + "  (exit $($r.exit))") -ForegroundColor Red
        $r.output -split "`n" | Where-Object { $_ -match "ERROR|error" } |
            ForEach-Object { Write-Host "        $_" -ForegroundColor Red }
        $failed++
    }
}

# — Error tests
Write-Host ""
Write-Host "  ERROR TESTS  (expect exit != 0)" -ForegroundColor Yellow
Write-Host "  ----------------------------------" -ForegroundColor Yellow

foreach ($t in $error_tests) {
    $r = Run-Test $t.file $false
    if ($r.ok) {
        Write-Host ("  PASS  " + $t.file) -ForegroundColor Green
        $passed++
    } else {
        Write-Host ("  FAIL  " + $t.file + "  (exit $($r.exit), compiler did not error)") -ForegroundColor Red
        $failed++
    }
}

# — Summary
Write-Host ""
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ("  Total: " + ($passed + $failed) + "  |  Passed: $passed  |  Failed: $failed") -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""
