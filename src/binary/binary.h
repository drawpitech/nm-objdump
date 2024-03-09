/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** binary
*/

#pragma once

#include <elf.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>

#define IS_64(bin) (!!((bin)->mem[EI_CLASS] == ELFCLASS64))
#define VC(e) (void *)(e)

#define EC(a, e) ((Elf##a##_Ehdr *)VC(e))
#define EHDR(b, a) EC(a, (b)->mem)
#define GETEHDR(b, i) (void *)(IS_64(b) ? &EHDR(b, 64)[i] : &EHDR(b, 32)[i])
#define GETEHDRA(b, i, a) (IS_64(b) ? EHDR(b, 64)[i].a : EHDR(b, 32)[i].a)

#define SC(a, e) ((Elf##a##_Shdr *)VC(e))
#define SHDR(b, a) SC(a, (b)->mem + GETEHDRA(b, 0, e_shoff))
#define GETSHDR(b, i) (IS_64(b) ? VC(&SHDR(b, 64)[i]) : VC(&SHDR(b, 32)[i]))
#define GETSHDRA(b, i, a) (IS_64(b) ? SHDR(b, 64)[i].a : SHDR(b, 32)[i].a)

#define TOSHDR(b, s, a) (IS_64(b) ? SC(64, s)->a : SC(32, s)->a)

#define _SHSTRTAB(b) GETSHDRA(b, GETEHDRA(b, 0, e_shstrndx), sh_offset)
#define SHSTRTAB(b) (char *)((b)->mem + _SHSTRTAB(b))

typedef struct {
    char filename[PATH_MAX];
    int fd;
    struct stat st;
    uint8_t *mem;
    uint16_t args;
} binary_t;

binary_t *binary_open(binary_t *bin);
void binary_free(binary_t *bin);
void *binary_get_type(binary_t *bin, uint32_t type);
void *binary_get_table(binary_t *bin, uint32_t type, const char *name);
