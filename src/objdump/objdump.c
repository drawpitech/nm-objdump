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

const file_type_t *get_archi(const binary_t *bin)
{
    const file_type_t *arch = NULL;
    uint32_t e_machine = GETEHDRA(bin, 0, e_machine);

    if (e_machine >= LEN_OF(HEADER_TYPE))
        return &HEADER_TYPE[0];
    arch = &HEADER_TYPE[e_machine];
    return (arch->type != 0) ? arch : &HEADER_TYPE[0];
}

static int exec_objdump(binary_t *bin)
{
    printf(
        "\n%s:     file format elf%d-%s\n", bin->filename,
        (GETEHDRA(bin, 0, e_ident)[EI_CLASS] == ELFCLASS32) ? 32 : 64,
        get_archi(bin)->type);
    if (bin->args & FLG_HEADER && print_header(bin) == RET_ERROR)
        return RET_ERROR;
    printf("\n");
    if (bin->args & FLG_FULL_CONTENT && print_full(bin) == RET_ERROR)
        return RET_ERROR;
    binary_free(bin);
    return RET_VALID;
}

int my_objdump(UNUSED int argc, char **argv)
{
    binary_t bin = {0};
    int ret = RET_VALID;

    if (!get_args(argv, &bin, LEN_OF(OB_ARGS), OB_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    if (bin.args == 0) {
        print_help(LEN_OF(OB_ARGS), OB_ARGS);
        return RET_ERROR;
    }
    ret |= exec_objdump(&bin);
    return ret;
}
