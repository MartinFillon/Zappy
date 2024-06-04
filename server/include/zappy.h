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
    client_t clients[SOMAXCONN];
} zappy_t;

/**
 * @brief Initialize the game structure
 *
 * @param args the parsed command line arguments
 * @return game_t the initialized game structure
 */
game_t init_game(args_infos_t *args);
void destroy_game(game_t *game);

/**
 * @brief Initialize the server structure
 *
 * @param args the parsed command line arguments
 * @param z the zappy structure containing the game and server structures
 * @return int 0 if success, 84 if error
 */
int init_program(args_infos_t *args, zappy_t *z);
void handle_server_cmd(char const *cmd, zappy_t *serv);
void destroy_program(zappy_t *z);
