/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdarg.h>
#include <sys/types.h>

#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/game.h"

#define TYPE client_t
#define NAME client_list
#include "vector.h"

/**
 * @brief Initialize the client
 *
 * @param fd the file descriptor
 * @param address the address of the client
 */
client_t init_client(int fd, char *address, uint32_t port);

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
 * @param clients all the other clients to broadcast messages
 */
void close_client(client_t *c, struct client_list *clients);

/**
 * @brief Erase client from @param clients at idx @param i
 *        from every structures: @param clients and @param ais
 *
 * @param clients All the clients connected
 * @param ais All the ais connected
 * @param i idx of the client in @param clients
 */
void kill_ai(struct client_list *clients, struct vector_ai_t *ais, size_t i);

/**
 * @brief Make an ai eat
 *
 * @param cli the client that will eat.
 * @param clients All the clients connected in the server.
 * @param n the number of the client
 */
void make_ai_eat(client_t *cli, struct client_list *clients, int n);

/**
 * @brief init the ai
 * @param game the game structure
 * @param client the client structure
 * @param team the team structure
 * @param the clients
 * @return true if success, false if error
 */
bool init_ai(
    game_t *game,
    client_t *restrict client,
    team_t *team,
    struct client_list *restrict clients
);
void destroy_ai(ai_t *ai);
/**
 * @brief Move the @param ai with respect with his direction
 * @param ai the ai to move
 * @param dir Direction where to move
 * @param map The map where to move the ai
 */
void move_ai(ai_t *ai, enum direction dir, map_t *map);

/**
 * @brief Move the position @param pos with respect of his direction
 * @param pos the position to move
 * @param dir The direction where to move
 * @param map The map where to move the ai
 */
void move_by_dir(pos_t *pos, enum direction dir, map_t *map);

/**
 * @brief Broadcast a message to all fds
 *
 * @param v the vector of fds
 * @param fmt the message to send
 */
void broadcast(struct vector_int *v, char *fmt, ...);

/**
 * @brief Prepare the response of the client in his @param io parameter.
 * @param io Input/Output structure containing the response buffer/size
 * @param fmt the message to send
 * @param args the arguments to replace in the message
 */
void prepare_response_cat_va(io_t *io, char *fmt, va_list args);

/**
 * @brief Broadcast a message to all clients of a specific type
 *
 * @param type the type of the client
 * @param clients the list of clients
 * @param fmt the message to send
 */
void broadcast_to(
    enum client_type_e type,
    struct client_list *clients,
    char *fmt,
    ...
);

/**
 * @brief Destroy the client
 * @param c the client structure
 */
void destroy_client(client_t *c);
