#!/bin/sh
set -eu

out="$("${1:-}")"
test "${out:-}" = "$(command pwd)"
