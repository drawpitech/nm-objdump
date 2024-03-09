/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** header
*/

#include <stdio.h>
#include <string.h>

#include "objdump.h"
#include "utils.h"

int print_header(binary_t *bin)
{
    const header_flag_t *flag = NULL;
    uint32_t e_type = GETEHDRA(bin, 0, e_type);

    if (bin == NULL)
        return RET_ERROR;
    flag = &FLAGS[(e_type < LEN_OF(FLAGS)) ? e_type : 0];
    printf(
        "architecture: %s, flags 0x%08x:\n"
        "%s\n"
        "start address 0x%016lx\n",
        get_archi(bin)->archi, flag->flag, flag->str,
        GETEHDRA(bin, 0, e_entry));
    return RET_VALID;
}
