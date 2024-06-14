/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** zappy
*/

#pragma once

#include "core/server.h"
#include "core/types/game.h"

typedef struct zappy_s {
    game_t game;
    server_t server;
    struct client_list *clients;
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

/**
 * @brief Handles the server command line
 *
 * @param cmd the command string
 * @param serv the full zappy program
 */
void handle_server_cmd(char const *cmd, zappy_t *serv);

/**
 * @brief Destroys and free the program
 *
 * @param z the program data
 */
void destroy_program(zappy_t *z);

/**
 * @brief check if its the program end by looking if an ai reached lvl 8
 *
 * @param list all the currently connected clients
 * @return bool true if the game ended, false if not
 */
bool check_end(struct client_list *list);
