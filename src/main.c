/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>

#include "utils.h"

int noprog(UNUSED int argc, UNUSED char **argv)
{
    dprintf(
        STDERR_FILENO,
        "no programe defined.\n"
        "recompile with -D PROG=\"nm\"");
    return 0;
}

int main(int argc, char **argv)
{
    return PROG(argc, argv);
}
