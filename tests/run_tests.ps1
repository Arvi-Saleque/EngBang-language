# EngBang Compiler — Full Test Suite
# Run from project root:
#   powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1

$compiler = ".\compiler.exe"
$testDir  = ".\tests"

# --- SUCCESS TESTS (compiler must exit 0) -----------------------------------
$success_tests = @(
    @{ file = "test_01_variables.txt";            expect = "10, 3.14, EngBang, 1" },
    @{ file = "test_02_constants_cast.txt";       expect = "100, 0, 5" },
    @{ file = "test_03_arithmetic.txt";           expect = "13, 7, 30, 3" },
    @{ file = "test_04_update.txt";               expect = "10, 20, hello, world, 3.5, 7" },
    @{ file = "test_05_conditional_if.txt";       expect = "x equals 10, done" },
    @{ file = "test_06_conditional_ifelse.txt";   expect = "fail, pass" },
    @{ file = "test_07_conditional_multi.txt";    expect = "x is >=5, y is <5" },
    @{ file = "test_08_loop_inc.txt";             expect = "1 2 3 4 5" },
    @{ file = "test_09_loop_dec.txt";             expect = "5 4 3 2 1" },
    @{ file = "test_10_loop_newvar.txt";          expect = "0 1 2 3 4" },
    @{ file = "test_11_functions.txt";            expect = "10, 20, -8" },
    @{ file = "test_12_functions_forward.txt";    expect = "12, 16" },
    @{ file = "test_13_combined.txt";             expect = "15, 10, total is 10" }
)

# --- ERROR TESTS (compiler must exit != 0) -----------------------------------
$error_tests = @(
    @{ file = "err_01_undeclared.txt";            expect = "undeclared variable" },
    @{ file = "err_02_redeclaration.txt";         expect = "redeclaration" },
    @{ file = "err_03_type_mismatch_decl.txt";    expect = "type mismatch in declaration" },
    @{ file = "err_04_type_mismatch_update.txt";  expect = "type mismatch in update" },
    @{ file = "err_05_const_update.txt";          expect = "cannot update constant" },
    @{ file = "err_06_cast_mismatch.txt";         expect = "cast type mismatch" },
    @{ file = "err_07_cond_undeclared.txt";       expect = "undeclared in conditional" },
    @{ file = "err_08_cond_type_mismatch.txt";    expect = "type mismatch in conditional" },
    @{ file = "err_09_return_type.txt";           expect = "return type mismatch" },
    @{ file = "err_10_loop_end_var.txt";          expect = "loop end variable mismatch" },
    @{ file = "err_11_loop_ctrl_var.txt";         expect = "loop control variable mismatch" },
    @{ file = "err_12_syntax_pipe.txt";           expect = "syntax error (missing pipe)" },
    @{ file = "err_13_syntax_keyword.txt";        expect = "syntax error (bad keyword)" }
)

# ---------------------------------------------------------------------------
$passed = 0
$failed = 0

function Run-Test($file, $expectPass) {
    $path   = Join-Path $testDir $file
    $output = Get-Content $path | & $compiler 2>&1
    $exit   = $LASTEXITCODE
    $ok     = if ($expectPass) { $exit -eq 0 } else { $exit -ne 0 }
    return @{ ok = $ok; exit = $exit; output = $output }
}

Write-Host ""
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   EngBang Compiler  —  Test Suite" -ForegroundColor Cyan
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
        $r.output | Where-Object { $_ -match "ERROR" } |
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
        $msg = ($r.output | Where-Object { $_ -match "ERROR" } | Select-Object -First 1)
        Write-Host ("  PASS  " + $t.file + "  ->  " + $msg) -ForegroundColor Green
        $passed++
    } else {
        Write-Host ("  FAIL  " + $t.file + "  (expected error but exit was 0)") -ForegroundColor Red
        $failed++
    }
}

# — Summary
Write-Host ""
Write-Host "==========================================" -ForegroundColor Cyan
$color = if ($failed -eq 0) { "Green" } else { "Red" }
Write-Host ("  Results: $passed passed,  $failed failed  (total " + ($passed + $failed) + ")") -ForegroundColor $color
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""
