/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** zappy
*/

#pragma once

#include "server.h"
#include "types/game.h"

typedef struct zappy_s {
    game_t game;
    server_t server;
} zappy_t;

game_t init_game(args_infos_t *args);
int init_program(args_infos_t *args, zappy_t *z);
vector_ai_t *init_ais(size_t ais_count);
