/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** binary
*/

#include <elf.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"

static bool get_file(binary_t *bin)
{
    bin->fd = open(bin->filename, O_RDONLY);
    if (bin->fd < 0)
        return ret_error("open", false, NULL);
    if (fstat(bin->fd, &bin->st) < 0)
        return ret_error("fstat", false, NULL);
    bin->mem = mmap(NULL, bin->st.st_size, PROT_READ, MAP_SHARED, bin->fd, 0);
    if (bin->mem == MAP_FAILED)
        return ret_error("mmap", false, NULL);
    return true;
}

binary_t *binary_open(binary_t *bin)
{
    if (bin == NULL)
        return NULL;
    if (!get_file(bin)) {
        binary_free(bin);
        return NULL;
    }
    if (memcmp(GETEHDRA(bin, 0, e_ident), ELFMAG, SELFMAG) != 0) {
        ret_error(bin->filename, 0, "File format not recognized\n");
        binary_free(bin);
        return NULL;
    }
    return bin;
}

void binary_free(binary_t *bin)
{
    if (bin == NULL)
        return;
    if (bin->fd > 0)
        close(bin->fd);
    if (bin->mem != NULL)
        munmap(bin->mem, bin->st.st_size);
    memset(bin, 0, sizeof(binary_t));
}

void *binary_get_type(binary_t *bin, uint32_t type)
{
    uint16_t num = GETEHDRA(bin, 0, e_shnum);

    for (int i = 0; i < num; i++)
        if (GETSHDRA(bin, i, sh_type) == type)
            return GETSHDR(bin, i);
    return NULL;
}

void *binary_get_table(binary_t *bin, uint32_t type, const char *name)
{
    const char *const shstrtab = SHSTRTAB(bin);
    uint16_t num = GETEHDRA(bin, 0, e_shnum);

    for (int i = 0; i < num; i++)
        if ((type == 0 || GETSHDRA(bin, i, sh_type) == type) &&
            strcmp(shstrtab + GETSHDRA(bin, i, sh_name), name) == 0)
            return GETSHDR(bin, i);
    return NULL;
}
