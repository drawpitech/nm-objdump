#!/usr/bin/env bash

dir=$(mktemp -d)

got="$dir/got"
exp="$dir/exp"

nix run .#nm -- "$@" > $got
nm "$@" > $exp
vimdiff $got $exp
