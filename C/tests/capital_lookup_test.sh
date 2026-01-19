#!/usr/bin/env bash
set -euo pipefail

# 簡易テスト: capital_lookup の入出力を確認する
ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)
SRC="$ROOT_DIR/class_12/capital_lookup.c"
BIN="$ROOT_DIR/class_12/capital_lookup"

# ビルド
clang "$SRC" -o "$BIN"

echo "[TEST] JAPAN -> TOKYO"
echo "JAPAN" | "$BIN" | tee /dev/stderr | grep -q "TOKYO"

echo "[TEST] japan(lower) -> TOKYO"
echo "japan" | "$BIN" | tee /dev/stderr | grep -q "TOKYO"

echo "[TEST] Unknown country -> not found"
echo "BRAZIL" | "$BIN" | tee /dev/stderr | grep -q "データに見当たりません"

echo "All tests passed."