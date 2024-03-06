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
    Elf64_Shdr *start_addr = NULL;

    if (!get_args(argv, &bin, LEN_OF(OB_ARGS), OB_ARGS) ||
        binary_open(&bin) == NULL)
        return RET_ERROR;
    start_addr = binary_get_table(&bin, 0, ".init");
    if (start_addr == NULL) {
        binary_free(&bin);
        fprintf(stderr, "%s: No section named .init\n", PROGNAME);
        return RET_ERROR;
    }
    printf(
        "\n%s:     file format %s\n"
        "architecture: i386:%s, flags 0x%08lx:\n"
        "\n"
        "start address 0x%016lx\n\n",
        bin.filename, "elf64-x86-64", "x86-64", bin.shdr->sh_flags,
        start_addr->sh_addr);
    binary_free(&bin);
    return RET_VALID;
}
