/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#include "utils.h"

#include <stdio.h>
#include <unistd.h>

int ret_error(const char *name, int value)
{
    dprintf(STDERR_FILENO, "%s: ", PROGNAME);
    perror(name);
    return value;
}
