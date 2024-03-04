/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** nm
*/

#pragma once

#include "elf.h"

typedef struct {
    const char *name;
    Elf64_Sym *symbol;
} symbol_t;
