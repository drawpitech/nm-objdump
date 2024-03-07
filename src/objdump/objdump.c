/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** objdump
*/

#include "objdump.h"

#include <stdio.h>
#include <string.h>

#include "utils.h"

const char *get_archi(const binary_t *bin)
{
    const char *arch = NULL;

    if (bin->ehdr->e_machine >= LEN_OF(EVENT_TABLE))
        return EVENT_TABLE[0];
    arch = EVENT_TABLE[bin->ehdr->e_machine];
    return (arch != NULL) ? arch : EVENT_TABLE[0];
}

int my_objdump(UNUSED int argc, char **argv)
{
    binary_t bin = {0};

    if (!get_args(argv, &bin, LEN_OF(OB_ARGS), OB_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    printf(
        "\n%s:     file format elf%d-%s\n", bin.filename,
        (bin.ehdr->e_ident[EI_CLASS] == ELFCLASS32) ? 32 : 64,
        get_archi(&bin));
    if (bin.args & FLG_HEADER && print_header(&bin) == RET_ERROR)
        return RET_ERROR;
    printf("\n");
    if (bin.args & FLG_FULL_CONTENT && print_full(&bin) == RET_ERROR)
        return RET_ERROR;
    binary_free(&bin);
    return RET_VALID;
}
