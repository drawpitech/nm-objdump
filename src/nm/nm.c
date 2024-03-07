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
        while (!isalnum(*str1) && *str1)
            str1++;
        while (!isalnum(*str2) && *str2)
            str2++;
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

int my_nm(UNUSED int argc, char **argv)
{
    binary_t bin = {0};
    Elf64_Shdr *symbols_shdr = NULL;
    Elf64_Shdr *strtab_shdr = NULL;
    symbol_t *symbols = NULL;

    if (!get_args(argv, &bin, LEN_OF(NM_ARGS), NM_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    symbols_shdr = binary_get_type(&bin, SHT_SYMTAB);
    strtab_shdr = binary_get_table(&bin, SHT_STRTAB, ".strtab");
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
