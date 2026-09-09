#!/bin/sh
set -eu

out="$("${1:-}" "/path/to/example.suffix" ".suffix")"

test "${out:-}" = "example"
