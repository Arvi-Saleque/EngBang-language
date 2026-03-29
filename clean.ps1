# clean.ps1 — Remove all generated and compiled files
# Run from project root:
#   powershell -ExecutionPolicy Bypass -File clean.ps1

$files = @(
    "src\parser.tab.c",
    "src\parser.tab.h",
    "src\lex.yy.c",
    "compiler.exe"
)

foreach ($f in $files) {
    if (Test-Path $f) {
        Remove-Item $f -Force
        Write-Host "Removed: $f"
    }
}

Write-Host "Done. Run 'mingw32-make' to rebuild."
