/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_name_flag
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "args_info.h"

static size_t get_nb_team(char const **av, size_t idx)
{
    size_t count = 0;

    for (idx++; av[idx] != NULL && av[idx][0] != '-'; idx++)
        count++;
    return count;
}

static bool get_names(
    char const **av,
    size_t *idx,
    size_t nb_team,
    args_infos_t *args
)
{
    size_t max_idx = (*idx) + nb_team;

    for (size_t i = 1; ((*idx) + i) < max_idx && av[(*idx) + i] != NULL; i++) {
        args->names[i] = strdup(av[(*idx) + i]);
        if (!args->names[i])
            return false;
    }
    args->names[nb_team] = NULL;
    *idx = max_idx;
    return true;
}

bool parse_names(char const **av, size_t *idx, args_infos_t *args)
{
    size_t nb_team = get_nb_team(av, *idx);

    if (!nb_team) {
        logger_error("No team provided for '-n' option.");
        return false;
    }
    args->names = malloc(sizeof(*args->names) * (nb_team + 1));
    if (!args->names || !get_names(av, idx, nb_team, args)) {
        logger_error("Allocation error.");
        return false;
    }
    return true;
}
