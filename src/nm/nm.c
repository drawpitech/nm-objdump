/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** nm
*/

#include "nm.h"

#include <elf.h>
#include <fcntl.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"

static int cmp(const symbol_t *a, const symbol_t *b)
{
    return strcoll(a->name, b->name);
}

static void sort_symbols(size_t size, symbol_t symbols[size])
{
    setlocale(LC_CTYPE, "");
    setlocale(LC_COLLATE, "");
    qsort(
        symbols, size, sizeof *symbols,
        (int (*)(const void *, const void *))cmp);
}

static void print_nm(binary_t *bin, const symbol_t *symbols)
{
    uint64_t val = 0;

    if (symbols == NULL)
        return;
    for (size_t i = 0; symbols[i].name; i++) {
        val = SYMA(bin, symbols[i].symbol, 0, st_value);
        if (val == 0)
            printf("%16s", "");
        else
            printf("%016lx", val);
        printf(" %c %s\n", symbol_type(bin, symbols + i), symbols[i].name);
    }
}

static symbol_t *get_symbols(
    binary_t *bin, void *symbols_shdr, void *strtab_shdr)
{
    void *arr = bin->mem + TOSHDR(bin, symbols_shdr, sh_offset);
    const char *names =
        (const char *)(bin->mem + TOSHDR(bin, strtab_shdr, sh_offset));
    const size_t size = TOSHDR(bin, symbols_shdr, sh_size) /
                        TOSHDR(bin, symbols_shdr, sh_entsize);
    symbol_t *symbols = malloc(sizeof(*symbols) * (size + 1));
    size_t index = 0;

    if (symbols == NULL)
        return NULL;
    memset(symbols, 0, sizeof(*symbols) * (size + 1));
    for (size_t i = 0; i < size; i++) {
        if (SYMA(bin, arr, i, st_name) == 0 ||
            ST_TYPE(bin, arr, i) == STT_FILE)
            continue;
        symbols[index].name = names + SYMA(bin, arr, i, st_name);
        symbols[index].symbol = SYM(bin, arr, i);
        index += 1;
    }
    return sort_symbols(index, symbols), symbols;
}

static int exec_nm(binary_t *bin)
{
    void *symbols_shdr = NULL;
    void *strtab_shdr = NULL;
    symbol_t *symbols = NULL;

    symbols_shdr = binary_get_type(bin, SHT_SYMTAB);
    strtab_shdr = binary_get_table(bin, SHT_STRTAB, ".strtab");
    if (symbols_shdr == NULL || strtab_shdr == NULL) {
        fprintf(stderr, "Failed to find the symbol/string table section.\n");
        binary_free(bin);
        return RET_ERROR;
    }
    symbols = get_symbols(bin, symbols_shdr, strtab_shdr);
    print_nm(bin, symbols);
    binary_free(bin);
    free(symbols);
    return RET_VALID;
}

int my_nm(UNUSED int argc, char **argv)
{
    binary_t bin = {0};
    int ret = RET_VALID;

    if (!get_args(argv, &bin, LEN_OF(NM_ARGS), NM_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    ret |= exec_nm(&bin);
    return ret;
}
