#!/usr/bin/env bash

nix run .#nm -- "$@" > got.txt
nm "$@" > exp.txt
vimdiff got.txt exp.txt
