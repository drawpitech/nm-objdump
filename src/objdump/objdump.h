/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** objdump
*/

#pragma once

#include "flags.h"
#include "utils.h"

#define OBJ_LINE_SIZE (16)

enum {
    FLG_HEADER = 1 << 0,
    FLG_FULL_CONTENT = 1 << 1,
};

typedef struct {
    const char *archi;
    const char *type;
} file_type_t;

static const file_type_t HEADER_TYPE[] = {
    [EM_NONE] = { "Unknown", "Unknown" },
    [EM_X86_64] = { "i386:x86-64", "x86-64" },
    [EM_386] = { "i386", "i386" },
};

typedef struct {
    uint32_t flag;
    const char *str;
} header_flag_t;

static const header_flag_t FLAGS[] = {
    [ET_NONE] = {0, ""},
    [ET_REL] = {HAS_SYMS | HAS_RELOC, "HAS_RELOC, HAS_SYMS"},
    [ET_EXEC] = {D_PAGED | HAS_SYMS | EXEC_P, "EXEC_P, HAS_SYMS, D_PAGED"},
    [ET_DYN] = {D_PAGED | DYNAMIC | HAS_SYMS, "HAS_SYMS, DYNAMIC, D_PAGED"},
};

static const arg_t OB_ARGS[] = {
    {FLG_HEADER, 'f', "file-header",
        "Display the contents of the overall file header"},
    {FLG_FULL_CONTENT, 's', "full-content",
        "Display the full contents of all sections requested"},
};

int print_header(binary_t *bin);
int print_full(binary_t *bin);
const file_type_t *get_archi(const binary_t *bin);
