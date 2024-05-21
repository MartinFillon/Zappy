/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_cmd_line
*/

#include "parsing_handler.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// @brief All args will be init to -1 or NULL, to check in continue
///        redefinition of command line argument.
static void init_args(args_infos_t *args)
{
    args->clients_nb = -1;
    args->freq = -1;
    args->height = -1;
    args->width = -1;
    args->port = -1;
    args->team_count = 0;
    args->names = NULL;
}

static bool check_args(args_infos_t *args)
{
    if (args->freq == -1)
        args->freq = 100;
    if (args->clients_nb == -1 || args->height == -1 ||
        args->width == -1 || args->port == -1 || args->names == NULL) {
        logger_error("Options are missing.");
        return false;
    }
    return true;
}

static bool handle_flags(char const **av, size_t *idx, args_infos_t *args)
{
    for (size_t i = 0; handlers[i].flag != NULL; i++) {
        if (!strcmp(av[*idx], handlers[i].flag))
            return handlers[i].handler(av, idx, args);
    }
    return false;
}

/// @brief Parse all the command line and put its informations inside args.
/// @return Boolean that indicates whether the command line is invalid or not.
bool parse_command_line(char const **av, args_infos_t *args)
{
    init_args(args);
    for (size_t i = 1; av[i] != NULL; i++) {
        if (av[i][0] != '-')
            return false;
        if (!handle_flags(av, &i, args))
            return false;
    }
    return check_args(args);
}
