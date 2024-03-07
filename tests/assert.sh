#!/usr/bin/env bash

nix run .#objdump -- "$@" > got.txt
objdump "$@" > exp.txt
vimdiff got.txt exp.txt
