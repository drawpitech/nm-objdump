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

int my_objdump(UNUSED int argc, char **argv)
{
    binary_t bin = {0};

    if (!get_args(argv, &bin, LEN_OF(OB_ARGS), OB_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    if (bin.args & FLG_HEADER && print_header(&bin) == RET_ERROR) {
        binary_free(&bin);
        return RET_ERROR;
    }
    binary_free(&bin);
    return RET_VALID;
}
