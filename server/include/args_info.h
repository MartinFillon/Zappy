/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** args_info
*/

#pragma once

#include <stdbool.h>

typedef struct args_infos_s {
    int port;

    int width;
    int height;

    char **names;
    int clients_nb;

    int freq; // Default 100
} args_infos_t;

bool parse_command_line(char const **av, args_infos_t *args);
void display_help(void);
