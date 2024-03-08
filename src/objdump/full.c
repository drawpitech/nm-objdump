/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** full
*/

#include <ctype.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

#include "objdump.h"
#include "utils.h"

static void print_line(
    binary_t *bin, size_t addr_size, Elf64_Shdr *section, size_t offset)
{
    size_t size = MIN(16, section->sh_size - offset);
    size_t written = 0;
    char c = '\0';

    printf(" %0*lx ", MAX(4, (int)addr_size), section->sh_addr + offset);
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
    printf("%*s", 16 - size, "");
    printf("\n");
}

static void print_section(
    binary_t *bin, const char *const shstrtab, Elf64_Shdr *section)
{
    size_t max_addr_size = 0;

    if (section->sh_size == 0 || section->sh_type == SHT_NOBITS)
        return;
    max_addr_size =
        snprintf(NULL, 0, "%lx", section->sh_addr + section->sh_size - 1);
    printf("Contents of section %s:\n", &shstrtab[section->sh_name]);
    for (size_t i = 0; i < section->sh_size; i += 16)
        print_line(bin, max_addr_size, section, i);
}

int print_full(binary_t *bin)
{
    const char *const shstrtab =
        (char *)(bin->mem + bin->shdr[bin->ehdr->e_shstrndx].sh_offset);
    bool valid = true;
    static const char *ignored_sections[] = {
        ".bss", ".shstrtab", ".strtab", ".symtab"};

    for (int i = 0; i < bin->ehdr->e_shnum; i++) {
        for (size_t j = 0; valid && j < LEN_OF(ignored_sections); j++)
            valid =
                !!strcmp(&shstrtab[bin->shdr[i].sh_name], ignored_sections[j]);
        if (valid)
            print_section(bin, shstrtab, bin->shdr + i);
    }
    return RET_VALID;
}
