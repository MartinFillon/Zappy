/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** log_level
*/

#include <stdio.h>
#include "logger.h"
#include "parsing_handler.h"

bool parse_log_level(const char **av, size_t *idx, args_infos_t *args)
{
    args->level = set_log_level_from_str(av[*idx + 1]);
    (*idx)++;
    return true;
}
