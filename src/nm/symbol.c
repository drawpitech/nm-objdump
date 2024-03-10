/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** symbol
*/

#include <elf.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "nm.h"

static char get_section_symbol(uint32_t sh_type, uint64_t sh_flags)
{
    if (sh_type == SHT_NOBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'B';
    if (sh_type == SHT_NOTE && sh_flags == (SHF_ALLOC))
        return 'R';
    if (sh_type == SHT_FINI_ARRAY && sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'D';
    if (sh_type == SHT_INIT_ARRAY && sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'D';
    if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'D';
    if (sh_type == SHT_PROGBITS && sh_flags == SHF_ALLOC)
        return 'R';
    if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'D';
    if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        return 'T';
    if (sh_type == SHT_DYNAMIC)
        return 'D';
    return (sh_flags != SHF_WRITE) ? 'R' : '?';
}

static char get_symbol(binary_t *bin, const symbol_t *sym)
{
    uint32_t bind = ST_BIND(bin, sym->symbol, 0);
    uint32_t type = ST_TYPE(bin, sym->symbol, 0);
    uint16_t ndx = SYMA(bin, sym->symbol, 0, st_shndx);

    if (bind == STB_GNU_UNIQUE)
        return 'u';
    if (bind == STB_WEAK)
        return ((type == STT_OBJECT) ? 'V' : 'W') | (ndx == SHN_UNDEF) * 0x20;
    if (ndx == SHN_UNDEF)
        return 'U';
    if (ndx == SHN_ABS)
        return 'A';
    if (ndx == SHN_COMMON)
        return 'C';
    if (ndx < SHN_LORESERVE)
        return get_section_symbol(
            GETSHDRA(bin, ndx, sh_type), GETSHDRA(bin, ndx, sh_flags));
    return '?';
}

char symbol_type(binary_t *bin, const symbol_t *sym)
{
    return get_symbol(bin, sym) |
        (ST_BIND(bin, sym->symbol, 0) == STB_LOCAL) * 0x20;
}
