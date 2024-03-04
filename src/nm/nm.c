/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** nm
*/

#include "nm.h"

#include <ctype.h>
#include <elf.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../utils.h"

static int cmp(const symbol_t *a, const symbol_t *b)
{
    const char *str1 = a->name;
    const char *str2 = b->name;

    while (true) {
        for (; !isalpha(*str1) && *str1; str1++)
            ;
        for (; !isalpha(*str2) && *str2; str2++)
            ;
        if (!*str1 || !*str2)
            return *str1 - *str2;
        if (tolower(*str1) != tolower(*str2))
            return tolower(*str1) - tolower(*str2);
        str1 += 1;
        str2 += 1;
    }
}

static void print_nm(const symbol_t *symbols)
{
    for (size_t i = 0; symbols[i].name; i++) {
        if (symbols[i].symbol->st_value == 0)
            printf("%16s", "");
        else
            printf("%016lx", symbols[i].symbol->st_value);
        printf(" %s\n", symbols[i].name);
    }
}

static Elf64_Shdr *find_type(binary_t *bin, Elf64_Word type)
{
    for (int i = 0; i < bin->ehdr->e_shnum; i++)
        if (bin->shdr[i].sh_type == type)
            return bin->shdr + i;
    return NULL;
}

static Elf64_Shdr *find_table(binary_t *bin, Elf64_Word type, const char *name)
{
    const char *const shstrtab =
        (char *)(bin->mem + bin->shdr[bin->ehdr->e_shstrndx].sh_offset);

    for (int i = 0; i < bin->ehdr->e_shnum; i++)
        if (bin->shdr[i].sh_type == type &&
            strcmp(shstrtab + bin->shdr[i].sh_name, name) == 0)
            return bin->shdr + i;
    return NULL;
}

static symbol_t *get_symbols(
    binary_t *bin, Elf64_Shdr *symbols_shdr, Elf64_Shdr *strtab_shdr)
{
    Elf64_Sym *arr = (Elf64_Sym *)(bin->mem + symbols_shdr->sh_offset);
    const char *names = (const char *)(bin->mem + strtab_shdr->sh_offset);
    const size_t size = symbols_shdr->sh_size / symbols_shdr->sh_entsize;
    symbol_t *symbols = malloc(sizeof(*symbols) * (size + 1));
    size_t index = 0;

    if (symbols == NULL)
        return NULL;
    memset(symbols, 0, sizeof(*symbols) * (size + 1));
    for (size_t i = 0; i < size; i++) {
        if (arr[i].st_name == 0 && ELF64_ST_BIND(arr[i].st_info) == STB_LOCAL)
            continue;
        symbols[index].name = names + arr[i].st_name;
        symbols[index].symbol = arr + i;
        index += 1;
    }
    qsort(
        symbols, index, sizeof(*symbols),
        (int (*)(const void *, const void *))cmp);
    return symbols;
}

int my_nm(int argc, char **argv)
{
    binary_t bin = {0};
    Elf64_Shdr *symbols_shdr = NULL;
    Elf64_Shdr *strtab_shdr = NULL;
    symbol_t *symbols = NULL;

    if (!get_args(argc, argv, &bin) || binary_open(&bin) == NULL)
        return RET_ERROR;
    symbols_shdr = find_type(&bin, SHT_SYMTAB);
    strtab_shdr = find_table(&bin, SHT_STRTAB, ".strtab");
    if (symbols_shdr == NULL || strtab_shdr == NULL) {
        fprintf(stderr, "Failed to find the symbol/string table section.\n");
        binary_free(&bin);
        return RET_ERROR;
    }
    symbols = get_symbols(&bin, symbols_shdr, strtab_shdr);
    print_nm(symbols);
    binary_free(&bin);
    free(symbols);
    return RET_VALID;
}
