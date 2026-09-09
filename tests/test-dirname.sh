#!/bin/sh
set -eu

out="$("${1:-}" "/path/to/example")"

test "${out:-}" = "/path/to"
