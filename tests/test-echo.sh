#!/bin/sh
set -eu

out="$("${1:-}" "-n" "hello world")"
test "${out:-}" = "$("printf" "hello world")"
