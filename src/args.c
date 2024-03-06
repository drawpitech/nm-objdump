/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** args
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

static bool set_flag(
    binary_t *bin, char c, size_t size, const arg_t options[size])
{
    for (size_t i = 0; i < size; i++) {
        if (options[i].c == c) {
            bin->args |= options[i].flag;
            return true;
        }
    }
    fprintf(stderr, "Invalid option: %c\n", c);
    return false;
}

static bool get_option(
    binary_t *bin, char const *str, size_t size, const arg_t options[size])
{
    bool err = false;

    if (*str != '-') {
        for (; *str; str++)
            err |= !set_flag(bin, *str, size, options);
        return !err;
    }
    str += 1;
    for (size_t i = 0; i < size; i++) {
        if (options[i].name != NULL && strcmp(options[i].name, str) == 0) {
            bin->args |= options[i].flag;
            return true;
        }
    }
    fprintf(stderr, "Invalid option `--%s`\n", str);
    return false;
}

static bool add_param(
    char *param, binary_t *bin, size_t size, const arg_t options[size])
{
    if (param == NULL || param[0] == '\0') {
        fprintf(stderr, "Invalid option `%s`\n", param);
        return false;
    }
    if (param[0] == '-')
        return get_option(bin, param + 1, size, options);
    if (bin->filename[0] != '\0') {
        fprintf(stderr, "Cannot handle multiple files");
        return false;
    }
    strcpy(bin->filename, param);
    return true;
}

static void print_help(size_t size, const arg_t options[size])
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
    char **argv, binary_t *bin, size_t size, const arg_t options[size])
{
    for (size_t i = 1; argv[i] != NULL; i++)
        if (!add_param(argv[i], bin, size, options))
            return false;
    if (bin->filename[0] == '\0') {
        print_help(size, options);
        return false;
    }
    return true;
}
