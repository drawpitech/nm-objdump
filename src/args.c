/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** args
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

static bool set_flag(
    flags_t *flags, char c, size_t size, const arg_t options[size])
{
    for (size_t i = 0; i < size; i++) {
        if (options[i].c == c) {
            flags->flag |= options[i].flag;
            return true;
        }
    }
    fprintf(stderr, "Invalid option: %c\n", c);
    return false;
}

static bool get_option(
    flags_t *flags, char const *str, size_t size, const arg_t options[size])
{
    bool err = false;

    if (*str != '-') {
        for (; *str; str++)
            err |= !set_flag(flags, *str, size, options);
        return !err;
    }
    str += 1;
    for (size_t i = 0; i < size; i++) {
        if (options[i].name != NULL && strcmp(options[i].name, str) == 0) {
            flags->flag |= options[i].flag;
            return true;
        }
    }
    fprintf(stderr, "Invalid option `--%s`\n", str);
    return false;
}

static bool add_param(
    flags_t *flags, char *param, size_t size, const arg_t options[size])
{
    if (param == NULL || param[0] == '\0') {
        fprintf(stderr, "Invalid option `%s`\n", param);
        return false;
    }
    if (param[0] == '-')
        return get_option(flags, param + 1, size, options);
    flags->nb_files += 1;
    flags->filenames = reallocarray(
        flags->filenames, flags->nb_files, sizeof *flags->filenames);
    if (flags->filenames == NULL)
        exit(RET_ERROR);
    flags->filenames[flags->nb_files - 1] = param;
    return true;
}

void print_help(size_t size, const arg_t options[size])
{
    printf("Usage: %s [options] <filename>\n", PROGNAME);
    printf("Options:\n");
    for (size_t i = 0; i < size; i++) {
        printf("\t");
        if (options[i].flag)
            printf("-%c ", options[i].c);
        if (options[i].name != NULL)
            printf("--%s", options[i].name);
        printf(":\t%s\n", options[i].desc);
    }
}

bool get_args(
    char **argv, flags_t *flags, size_t size, const arg_t options[size])
{
    for (size_t i = 1; argv[i] != NULL; i++)
        if (!add_param(flags, argv[i], size, options))
            return false;
    if (flags->flag & 1) {
        print_help(size, options);
        exit(RET_VALID);
    }
    if (flags->nb_files == 0) {
        print_help(size, options);
        return false;
    }
    return true;
}
