/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** nm
*/

#pragma once

#include "utils.h"

#define _S(s, a, i) (((Elf##a##_Sym *)(s)) + i)
#define SYM(b, s, i) (IS_64(b) ? (void *)_S(s, 64, i) : (void *)_S(s, 32, i))
#define SYMA(b, s, i, a) (IS_64(b) ? _S(s, 64, i)->a : _S(s, 32, i)->a)

#define _A(a, s, t) ELF##a##_ST_##t((s)->st_info)
#define _B(a, s, i, t) _A(a, _S(s, a, i), t)
#define ST_BIND(b, s, i) (IS_64(b) ? _B(64, s, i, BIND) : _A(32, s, i, TYPE))
#define ST_TYPE(b, s, i) (IS_64(b) ? _B(64, s, i, TYPE) : _B(32, s, i, TYPE))

enum {
    FLG_HELP = 1 << 0,
};

static const arg_t NM_ARGS[] = {
    {FLG_HELP, 'h', "help", "Display the help message"},
};

typedef struct {
    const char *name;
    void *symbol;
} symbol_t;
