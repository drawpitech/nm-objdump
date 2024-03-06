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
    Elf64_Shdr *start_addr = NULL;

    if (bin == NULL)
        return RET_ERROR;
    start_addr = binary_get_table(bin, 0, ".init");
    if (start_addr == NULL) {
        binary_free(bin);
        fprintf(stderr, "%s: No section named .init\n", PROGNAME);
        return RET_ERROR;
    }
    printf(
        "\n%s:     file format %s\n"
        "architecture: i386:%s, flags 0x%08lx:\n"
        "\n"
        "start address 0x%016lx\n\n",
        bin->filename, "elf64-x86-64", "x86-64", bin->shdr->sh_flags,
        start_addr->sh_addr);
    return RET_VALID;
}
