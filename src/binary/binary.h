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
#include <sys/stat.h>

typedef struct {
    char filename[PATH_MAX];
    int fd;
    struct stat st;
    unsigned char *mem;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    uint16_t args;
} binary_t;

binary_t *binary_open(binary_t *bin);
void binary_free(binary_t *bin);
Elf64_Shdr *binary_get_type(binary_t *bin, Elf64_Word type);
Elf64_Shdr *binary_get_table(binary_t *bin, Elf64_Word type, const char *name);
