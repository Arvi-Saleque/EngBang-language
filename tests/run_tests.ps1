# EngBang Compiler — Test Suite
# Run from project root:
#   powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1

$compiler = ".\compiler.exe"
$testDir  = ".\tests"

# ---------------------------------------------------------------------------
# Test definitions
# ---------------------------------------------------------------------------

$success_tests = @(
    @{ file = "success_all.txt"; expect = "All language features" }
)

$error_tests = @(
    @{ file = "err_01_undeclared.txt";          expect = "undeclared variable" },
    @{ file = "err_02_redeclaration.txt";       expect = "redeclaration" },
    @{ file = "err_03_type_mismatch_decl.txt";  expect = "type mismatch in declaration" },
    @{ file = "err_04_type_mismatch_update.txt";expect = "type mismatch in update" },
    @{ file = "err_05_const_update.txt";        expect = "cannot update constant" },
    @{ file = "err_06_cast_mismatch.txt";       expect = "cast type mismatch" },
    @{ file = "err_07_cond_undeclared.txt";     expect = "undeclared in conditional" },
    @{ file = "err_08_cond_type_mismatch.txt";  expect = "type mismatch in conditional" },
    @{ file = "err_09_cond_group_mismatch.txt"; expect = "group count mismatch" },
    @{ file = "err_10_return_type.txt";         expect = "return type mismatch" },
    @{ file = "err_11_func_arg_count.txt";      expect = "wrong argument count" },
    @{ file = "err_12_func_arg_type.txt";       expect = "argument type mismatch" },
    @{ file = "err_13_func_undefined.txt";      expect = "undefined function" },
    @{ file = "err_14_loop_end_var.txt";        expect = "loop end variable mismatch" },
    @{ file = "err_15_loop_ctrl_var.txt";       expect = "loop control variable mismatch" },
    @{ file = "err_16_loop_step_type.txt";      expect = "step type mismatch" },
    @{ file = "err_17_syntax_pipe.txt";         expect = "syntax error (missing pipe)" },
    @{ file = "err_18_syntax_keyword.txt";      expect = "syntax error (bad keyword)" },
    @{ file = "err_19_syntax_comparator.txt";   expect = "syntax error (direct comparator)" }
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
