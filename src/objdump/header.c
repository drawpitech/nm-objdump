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
    if (bin == NULL)
        return RET_ERROR;
    printf(
        "architecture: i386:%s, flags 0x%08lx:\n"
        "\n"
        "start address 0x%016lx\n\n",
        "x86-64", bin->shdr->sh_flags, bin->ehdr->e_entry);
    return RET_VALID;
}
