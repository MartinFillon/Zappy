/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** help
*/

#include <stdio.h>

#include "options/parser.h"

static void help(char const *bin, struct options *opts)
{
    dprintf(1, "Usage:\n\t%s [options]\n\nOptions:\n", bin);
    for (size_t i = 0; i < opts->size; i++)
        dprintf(1, "\t%s\n", opts->data[i].identifier);
}

bool run_help(char **av, struct options *opts)
{
    for (size_t i = 0; av[i]; i++) {
        if (strcmp(av[i], "-h") == 0 || strcmp(av[i], "--help") == 0) {
            help(av[0], opts);
            return true;
        }
    }
    return false;
}
