/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#pragma once

#include <elf.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

#include "binary/binary.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifndef PROG
    #define PROG noprog
#endif
#define PROGNAME TOSTRING(PROG)

#define ATTR(x) __attribute__((x))
#define UNUSED ATTR(unused)

#define LEN_OF(x) (sizeof(x) / sizeof *(x))

enum {
    RET_VALID = 0,
    RET_ERROR = 84,
};

typedef struct {
    uint16_t flag;
    char c;
    char *name;
    char *desc;
} arg_t;

typedef struct {
    uint32_t flag;
    char **filenames;
    size_t nb_files;
} flags_t;

int ret_error(const char *name, int value);
bool get_args(
    char **argv, flags_t *flags, size_t size, const arg_t options[size]);
void print_help(size_t size, const arg_t options[size]);

int noprog(int argc, char **argv);
int my_objdump(int argc, char **argv);
int my_nm(int argc, char **argv);
