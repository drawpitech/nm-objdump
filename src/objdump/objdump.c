/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** objdump
*/

#include <stdio.h>

#include "../utils.h"

int my_objdump(UNUSED int argc, UNUSED char **argv)
{
    binary_t bin = {0};

    if (!get_args(argc, argv, &bin) || binary_open(&bin) == NULL)
        return RET_ERROR;
    binary_free(&bin);
    return RET_VALID;
}
