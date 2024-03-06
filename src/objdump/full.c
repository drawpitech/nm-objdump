/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** header
*/

#include <unistd.h>

#include "objdump.h"
#include "utils.h"

static void print_section(
    binary_t *bin, const char *const shstrtab, Elf64_Shdr *section)
{
    if (section->sh_size == 0 || section->sh_type == SHT_NOBITS)
        return;
    printf("Content of section %s:", &shstrtab[section->sh_name]);
    for (size_t i = 0; i < section->sh_size; i++) {
        if (i % 16 == 0)
            printf("\n %lx ", section->sh_addr);
        printf("%02x", bin->mem[section->sh_offset + i]);
        if (i % 4 == 3)
            printf(" ");
    }
    printf("\n");
}

int print_full(binary_t *bin)
{
    const char *const shstrtab =
        (char *)(bin->mem + bin->shdr[bin->ehdr->e_shstrndx].sh_offset);

    for (int i = 0; i < bin->ehdr->e_shnum; i++)
        print_section(bin, shstrtab, bin->shdr + i);
    return RET_VALID;
}
