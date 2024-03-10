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

static void print_line(binary_t *bin, size_t addr_size, void *sec, size_t off)
{
    size_t size = MIN(16, TOSHDR(bin, sec, sh_size) - off);
    size_t w = 0;
    unsigned char c = '\0';

    printf(" %0*lx ", MAX(4, (int)addr_size), TOSHDR(bin, sec, sh_addr) + off);
    for (size_t i = 0; i < size; i++) {
        w += printf("%02x", bin->mem[TOSHDR(bin, sec, sh_offset) + off + i]);
        if (i % 4 == 3)
            w += printf(" ");
    }
    printf("%*s", (int)((OBJ_LINE_SIZE * 2 + 4) - w + 1), "");
    for (size_t i = 0; i < size; i++) {
        c = bin->mem[TOSHDR(bin, sec, sh_offset) + off + i];
        printf("%c", isprint(c) ? c : '.');
    }
    printf("%*s", (int)(OBJ_LINE_SIZE - size), "");
    printf("\n");
}

static void print_section(binary_t *bin, const char *name, void *section)
{
    size_t max_addr_size = 0;
    uint32_t sh_type = TOSHDR(bin, section, sh_type);
    uint32_t sh_size = TOSHDR(bin, section, sh_size);
    uint64_t sh_addr = TOSHDR(bin, section, sh_addr);

    if (sh_size == 0 || sh_type == SHT_NOBITS)
        return;
    max_addr_size = snprintf(NULL, 0, "%lx", sh_addr + sh_size - 1);
    printf("Contents of section %s:\n", name);
    for (size_t i = 0; i < sh_size; i += OBJ_LINE_SIZE)
        print_line(bin, max_addr_size, section, i);
}

static bool symbol_ignored(const char *name)
{
    static const char *const ignored_sections[] = {
        ".bss", ".shstrtab", ".strtab", ".symtab"};
    bool res = true;

    for (size_t i = 0; res && i < LEN_OF(ignored_sections); i++)
        res = !!strcmp(name, ignored_sections[i]);
    return res && strncmp(name, ".rela", 5);
}

int print_full(binary_t *bin)
{
    const char *const shstrtab = SHSTRTAB(bin);
    const char *name = NULL;
    uint16_t e_shnum = GETEHDRA(bin, 0, e_shnum);

    for (uint16_t i = 0; i < e_shnum; i++) {
        name = &shstrtab[GETSHDRA(bin, i, sh_name)];
        if (symbol_ignored(name))
            print_section(bin, name, GETSHDR(bin, i));
    }
    return RET_VALID;
}
