/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** utils
*/

#include "utils.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ret_error(const char *name, int value, const char *str)
{
    fprintf(stderr, "%s: ", PROGNAME);
    if (name != NULL && name[0] != '\0')
        fprintf(stderr, "%s: ", name);
    fprintf(stderr, "%s", (str != NULL) ? str : strerror(errno));
    return value;
}
