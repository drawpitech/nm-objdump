/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** nm
*/

#pragma once

#include "elf.h"
#include "utils.h"

enum {
    FLG_HELP = 1 << 0,
};

static const arg_t NM_ARGS[] = {
    {FLG_HELP, 'h', "help", "Display the help message"},
};

typedef struct {
    const char *name;
    Elf64_Sym *symbol;
} symbol_t;
