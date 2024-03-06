/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** objdump
*/

#pragma once

#include "utils.h"

enum {
    FLG_HEADER = 1 << 0,
    FLG_FULL_CONTENT = 1 << 1,
};

static const arg_t OB_ARGS[] = {
    {FLG_HEADER, 'f', "file-header",
     "Display the contents of the overall file header"},
    {FLG_FULL_CONTENT, 's', "full-content",
     "Display the full contents of all sections requested"},
};

int print_header(binary_t *bin);
