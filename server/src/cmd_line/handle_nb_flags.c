/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_flags
*/

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "args_info.h"
#include "utils.h"

static bool is_number(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

static bool parse_nbr(
    char const **av,
    size_t *idx,
    int *nbr
)
{
    if (av[(*idx) + 1] == NULL || av[(*idx) + 1][0] == '-') {
        logger_error("Argument not provided.\n");
        return false;
    }
    if (!is_number(av[(*idx + 1)])) {
        logger_error("Argument is not a number.\n");
        return false;
    }
    *nbr = atoi(av[(*idx) + 1]);
    (*idx)++;
    return true;
}

bool parse_height(char const **av, size_t *idx, args_infos_t *args)
{
    if (args->height != -1) {
        logger_error("Height already defined.\n");
        return false;
    }
    return parse_nbr(av, idx, &args->height);
}

bool parse_width(char const **av, size_t *idx, args_infos_t *args)
{
    if (args->width != -1) {
        logger_error("Width already defined.\n");
        return false;
    }
    return parse_nbr(av, idx, &args->width);
}

bool parse_port(char const **av, size_t *idx, args_infos_t *args)
{
    if (args->port != -1) {
        logger_error("Port already defined.\n");
        return false;
    }
    return parse_nbr(av, idx, &args->port);
}

bool parse_clients_nb(char const **av, size_t *idx, args_infos_t *args)
{
    if (args->clients_nb != -1) {
        logger_error("Clients_nb already defined.\n");
        return false;
    }
    return parse_nbr(av, idx, &args->clients_nb);
}

bool parse_frequency(char const **av, size_t *idx, args_infos_t *args)
{
    if (args->freq != -1) {
        logger_error("Frequency already defined.\n");
        return false;
    }
    return parse_nbr(av, idx, &args->freq);
}
