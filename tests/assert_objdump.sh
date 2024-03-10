#!/usr/bin/env bash

dir=$(mktemp -d)

got="$dir/got"
exp="$dir/exp"

nix run .#objdump -- "$@" > $got
objdump -fs "$@" > $exp
vimdiff $got $exp
