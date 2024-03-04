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

static bool is_valid_elf(binary_t *nm)
{
    if (nm->mem[0] == 0x7f && strncmp((char *)&nm->mem[1], "ELF", 3) == 0)
        return true;
    fprintf(stderr, "Not a valid ELF file.\n");
    return false;
}

static bool get_file(binary_t *bin)
{
    bin->fd = open(bin->filename, O_RDONLY);
    if (bin->fd < 0) {
        ret_error("open", 0);
        return false;
    }
    if (fstat(bin->fd, &bin->st) < 0) {
        ret_error("fstat", 0);
        return false;
    }
    return true;
}

static bool map_file(binary_t *bin)
{
    bin->mem = mmap(NULL, bin->st.st_size, PROT_READ, MAP_SHARED, bin->fd, 0);
    if (bin->mem == MAP_FAILED) {
        ret_error("mmap", RET_ERROR);
        return false;
    }
    bin->ehdr = (Elf64_Ehdr *)bin->mem;
    bin->shdr = (Elf64_Shdr *)(bin->mem + bin->ehdr->e_shoff);
    return true;
}

binary_t *binary_open(binary_t *bin)
{
    if (bin == NULL)
        return NULL;
    if (!get_file(bin) || !map_file(bin)) {
        binary_free(bin);
        return NULL;
    }
    return is_valid_elf(bin) ? bin : NULL;
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
