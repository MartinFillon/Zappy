/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parsing_handler
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "args_info.h"

typedef struct flags_handler_s {
    char *flag;
    bool (*handler)(char const **, size_t *, args_infos_t *);
} flags_handler_t;

bool parse_port(char const **av, size_t *idx, args_infos_t *args);
bool parse_width(char const **av, size_t *idx, args_infos_t *args);
bool parse_height(char const **av, size_t *idx, args_infos_t *args);
bool parse_clients_nb(char const **av, size_t *idx, args_infos_t *args);
bool parse_frequency(char const **av, size_t *idx, args_infos_t *args);

static const flags_handler_t handlers[] = {
    {"-p", parse_port},
    {"-x", parse_width},
    {"-y", parse_height},
    // {"-n", parse_names},
    {"-c", parse_clients_nb},
    {"-f", parse_frequency},
    {NULL, NULL}
};
