# nm/objdump

ELF exploration

> [!NOTE]
> This is a 2nd year project at Epitech, on the PSU (Unix System Programming)
> module.


## Description

The goal is to code an equivalent to the system commands nm without any options
and objdump with `-fs` option.

Both binaries support 32 and 64 bits architectures.
- relocatable files `.o` & `.a`
- shared files `.so`
- executable files


## Build

Using Nix, there is `nm` and `objdump` derivations in the flake.

On non-Nix systems, you can use the provided `Makefile`:

You will need:
- gcc
- gnumake
- glibc
```sh
make -j
```

## Bonus

There is a `Makefile` rule to build some files to tests.

The `objdump` command support following options:
- `-h`, `--help`: display the section headers
- `-f`, `--file-headers`: display the file header
- `-s`, `--full-contents`: display the section headers
