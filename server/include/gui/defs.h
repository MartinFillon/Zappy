/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** defs
*/

#pragma once

#include "types/client.h"

typedef struct gui_cmd_s {
    char *cmd;
    void (*func)(char *, client_t *, game_t *);
} gui_cmd_t;

void map_size(char *args, client_t *cli, game_t *game);
