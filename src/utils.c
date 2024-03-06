/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ret_error(const char *name, int value)
{
    dprintf(STDERR_FILENO, "%s: ", PROGNAME);
    perror(name);
    return value;
}

bool get_args(int argc, char **argv, binary_t *bin)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename>\n", PROGNAME);
        return false;
    }
    strcpy(bin->filename, argv[1]);
    return true;
}
