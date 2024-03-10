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
    uint8_t len = ADDRLEN(bin);

    if (symbols == NULL)
        return;
    for (size_t i = 0; symbols[i].name; i++) {
        if (symbols[i].c == 'U' || symbols[i].c == 'w' || symbols[i].c == 'v')
            printf("%*s", len, "");
        else
            printf("%0*lx", len, SYMA(bin, symbols[i].symbol, 0, st_value));
        printf(" %c %s\n", symbols[i].c, symbols[i].name);
    }
}

static symbol_t *get_symbols(binary_t *bin, void *symbols_shdr, void *strtab)
{
    void *arr = bin->mem + TOSHDR(bin, symbols_shdr, sh_offset);
    const char *names = ((char *)bin->mem + TOSHDR(bin, strtab, sh_offset));
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
        symbols[index].c = symbol_type(bin, symbols + index);
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
        binary_free(bin);
        return ret_error(
            "", RET_VALID,
            "Failed to find the symbol/string table section.\n");
    }
    symbols = get_symbols(bin, symbols_shdr, strtab_shdr);
    print_nm(bin, symbols);
    binary_free(bin);
    free(symbols);
    return RET_VALID;
}

static bool fill_bin(binary_t *bin, flags_t *flags, const char *filename)
{
    strcpy(bin->filename, filename);
    bin->args = flags->flag;
    return (binary_open(bin) != NULL);
}

int my_nm(UNUSED int argc, char **argv)
{
    binary_t bin = {0};
    flags_t flags = {0};
    int ret = RET_VALID;

    if (!get_args(argv, &flags, LEN_OF(NM_ARGS), NM_ARGS))
        return RET_ERROR;
    for (size_t i = 0; i < flags.nb_files; i++) {
        if (!fill_bin(&bin, &flags, flags.filenames[i])) {
            ret = RET_ERROR;
            continue;
        }
        printf((flags.nb_files > 1) ? "\n%s:\n" : "", flags.filenames[i]);
        ret |= exec_nm(&bin);
    }
    free(flags.filenames);
    return ret;
}
