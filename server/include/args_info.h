/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** args_info
*/

#pragma once

#include <stdbool.h>

#include "str.h"

typedef struct args_infos_s {
    int port;

    int width;
    int height;

    struct vector_str_t *names;
    int team_count;

    int clients_nb;

    int freq; // Default 100
    int level;
} args_infos_t;

/**
 * @brief Parse the command line arguments
 *
 * @param av the arguments
 * @param args the parsed arguments infos
 * @return true if success, false if error
 */
bool parse_command_line(char const **av, args_infos_t *args);

/**
 * @brief Display the help message
 */
void display_help(void);
