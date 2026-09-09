#!/bin/sh
set -eu

out="$(timeout 2 "${1:-}" hello world | head -n 3)"
test "${out:-}" = "hello world
hello world
hello world"
