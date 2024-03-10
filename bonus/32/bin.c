/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** bin
*/

#include <stdlib.h>
#include <string.h>

static void sort_me_daddy(int ac, char **av)
{
    qsort(
        av + 1, ac - 1, sizeof *av,
        (int (*)(const void *, const void *))strcmp);
}

int main(int ac, char **av)
{
    sort_me_daddy(ac, av);
    return 0;
}
