/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#pragma once

#include <elf.h>
#include <linux/limits.h>
#include <sys/stat.h>

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
    char filename[PATH_MAX];
    int fd;
    struct stat st;
    unsigned char *mem;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
} binary_t;

int ret_error(const char *name, int value);

binary_t *binary_open(binary_t *bin);
void binary_free(binary_t *bin);

int noprog(int argc, char **argv);
int my_objdump(int argc, char **argv);
int my_nm(int argc, char **argv);
