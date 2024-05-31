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
 * @brief Prepare the response of the client in his @param io parameter.
 *
 * @param io Input/Output structure containing the response buffer/size
 * @param fmt the message to send
 * @param ... the arguments to replace in the message
 */
void prepare_response(io_t *io, char *fmt, ...);

/**
 * @brief Add the formatted string from @param fmt and @param ... in the
 *        io response buffer
 *
 * @param io Input/Output structure containing the response buffer/size
 * @param fmt the message to use for concat
 * @param ... the arguments to replace in the message
 */
void prepare_response_cat(io_t *io, char *fmt, ...);

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
 * @brief Free and reset a buffer at 0
 *
 * @param buffer the buffer to be reseted
 */
void free_buffer(struct buffer_s *buffer);

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
bool init_ai(game_t *game, client_t *client, team_t *team);

/**
 * @brief Move the @param ai in y axis
 * @param ai the ai to move
 * @param dir the direction where to move it
 * @param map The map where to move the ai
 */
void move_ai_y(ai_t *ai, enum direction dir, map_t *map);

/**
 * @brief Move the @param ai in x axis
 * @param ai the ai to move
 * @param dir the direction where to move it
 * @param map The map where to move the ai
 */
void move_ai_x(ai_t *ai, enum direction dir, map_t *map);

/**
 * @brief Broadcast a message to all fds
 *
 * @param v the vector of fds
 * @param fmt the message to send
 */
void broadcast(struct vector_int *v, char *fmt, ...);
