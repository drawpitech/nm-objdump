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

static const char *const EVENT_TABLE[] = {
    [EM_X86_64] = "x86-64",
    [EM_386] = "i386",
};

int print_header(binary_t *bin)
{
    const char *arch = NULL;

    if (bin == NULL)
        return RET_ERROR;
    arch = EVENT_TABLE[bin->ehdr->e_machine];
    if (arch == NULL)
        arch = "Unknown";
    printf(
        "architecture: i386:%s, flags 0x%08lx:\n"
        "\n"
        "start address 0x%016lx\n",
        arch, bin->shdr->sh_flags, bin->ehdr->e_entry);
    return RET_VALID;
}
