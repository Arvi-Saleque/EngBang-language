#!/usr/bin/env bash
set -euo pipefail
COMPILER=${1:-./compiler_linux}
ROOT=$(cd "$(dirname "$0")" && pwd)

run_file() {
  local kind="$1"
  local file="$2"
  echo
  echo "===== [$kind] $file ====="
  if "$COMPILER" < "$ROOT/$file"; then
    echo "[PASS-RUN] $file"
  else
    echo "[FAIL-RUN] $file"
  fi
}

while IFS= read -r -d '' f; do run_file SUCCESS "${f#$ROOT/}"; done < <(find "$ROOT/success" -type f -name '*.txt' -print0 | sort -z)
while IFS= read -r -d '' f; do run_file ERROR   "${f#$ROOT/}"; done < <(find "$ROOT/errors"  -type f -name '*.txt' -print0 | sort -z)
