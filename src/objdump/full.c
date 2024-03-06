/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** header
*/

#include <ctype.h>
#include <sys/param.h>
#include <unistd.h>

#include "objdump.h"
#include "utils.h"

static void print_line(binary_t *bin, Elf64_Shdr *section, size_t offset)
{
    size_t size = MIN(16, section->sh_size - offset);
    size_t written = 0;
    char c = '\0';

    printf(" %04lx ", section->sh_addr + offset);
    for (size_t i = 0; i < size; i++) {
        written += printf("%02x", bin->mem[section->sh_offset + offset + i]);
        if (i % 4 == 3)
            written += printf(" ");
    }
    printf("%*s", (16 * 2 + 4) - written + 1, "");
    for (size_t i = 0; i < size; i++) {
        c = bin->mem[section->sh_offset + offset + i];
        printf("%c", isprint(c) ? c : '.');
    }
    printf("\n");
}

static void print_section(
    binary_t *bin, const char *const shstrtab, Elf64_Shdr *section)
{
    if (section->sh_size == 0 || section->sh_type == SHT_NOBITS)
        return;
    printf("Contents of section %s:\n", &shstrtab[section->sh_name]);
    for (size_t i = 0; i < section->sh_size; i += 16)
        print_line(bin, section, i);
}

int print_full(binary_t *bin)
{
    const char *const shstrtab =
        (char *)(bin->mem + bin->shdr[bin->ehdr->e_shstrndx].sh_offset);

    for (int i = 0; i < bin->ehdr->e_shnum; i++)
        print_section(bin, shstrtab, bin->shdr + i);
    return RET_VALID;
}
