/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include "types/client.h"

/**
 * @brief Initialize the client
 *
 * @param c the client structure
 * @param fd the file descriptor
 */
void init_client(client_t *c, int fd);

/**
 * @brief Send a message to the client
 *
 * @param client the client structure
 * @param fmt the message to send
 * @param ... the arguments to replace in the message
 */
void send_client(client_t *client, char *fmt, ...);

/**
 * @brief Read the client buffer
 *
 * @param client the client structure
 * @return int 0 if success, 84 if error
 */
int read_client(client_t *client);

/**
 * @brief entrypoint for ai clients
 *
 * @param line the command to execute
 * @param c the client structure
 * @param game the game structure
 * @param clients All the clients connected.
 * @return int 0 if success, 84 if error
 */
int ai_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
);

/**
 * @brief entrypoint for gui clients
 *
 * @param line the command to execute
 * @param c the client structure
 * @param game the game structure
 * @param clients All the clients connected.
 * @return int 0 if success, 84 if error
 */
int gui_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
);

/**
 * @brief entrypoint for unset clients
 *
 * @param line the command to execute
 * @param c the client structure
 * @param game the game structure
 * @param clients All the clients connected.
 * @return int 0 if success, 84 if error
 */
int unset_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
);

/**
 * @brief Close the client
 *
 * @param c the client structure
 */
void close_client(client_t *c);

/**
 * @brief Make an ai eat
 *
 * @param cli the client that will eat.
 * @param clients All the clients connected in the server.
 * @param n the number of the client
 */
void make_ai_eat(client_t *cli, client_t *clients, int n);

/**
 * @brief init the ai
 * @param game the game structure
 * @param client the client structure
 * @param team the team structure
 * @return true if success, false if error
 */
bool init_ai(game_t *game, client_t *client, team_t const *team);
