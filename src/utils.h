/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#pragma once

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

int ret_error(const char *name, int value);

int noprog(int argc, char **argv);
int my_objdump(int argc, char **argv);
int my_nm(int argc, char **argv);
