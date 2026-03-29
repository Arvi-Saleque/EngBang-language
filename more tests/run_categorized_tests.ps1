param(
    [string]$Compiler = ".\compiler.exe"
)

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path

function Run-TestFile {
    param(
        [string]$Kind,
        [string]$FilePath
    )

    Write-Host ""
    Write-Host "===== [$Kind] $FilePath ====="
    Get-Content $FilePath | & $Compiler
    Write-Host "EXIT CODE: $LASTEXITCODE"
}

Get-ChildItem (Join-Path $Root "success") -Recurse -Filter *.txt |
    Sort-Object FullName |
    ForEach-Object { Run-TestFile -Kind "SUCCESS" -FilePath $_.FullName }

Get-ChildItem (Join-Path $Root "errors") -Recurse -Filter *.txt |
    Sort-Object FullName |
    ForEach-Object { Run-TestFile -Kind "ERROR" -FilePath $_.FullName }
