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
    int team_count;

    int clients_nb;

    int freq; // Default 100
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
