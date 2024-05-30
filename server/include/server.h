/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once

#include <stdint.h>
#include <sys/select.h>
#include <sys/socket.h>

#include "types/client.h"
#include "types/game.h"
#include "args_info.h"

typedef struct server_s {
    int fd;
    fd_set read_fds;
    fd_set write_fds;
    struct router *router;
} server_t;

/**
 * @brief Initialize the server
 *
 * @param port the port to listen on
 * @return int 0 if success, 84 if error
 */
int server_init(uint32_t port);

/**
 * @brief Loop the server
 *
 * @param args the parsed command line arguments
 * @return int 0 if success, 84 if error
 */
int loop_server(args_infos_t *args);

/**
 * @brief Accept a new client
 *
 * @param s the server structure
 * @param clients All the clients connected.
 * @return int 0 if success, 84 if error
 */
int accept_new_client(server_t *s, client_t *clients);

/**
 * @brief Handle the buffer
 *
 * @param c the client structure
 * @param game the game structure
 * @param c All the clients connected
 * @return int 0 if success, 84 if error
 */
int handle_buffer(client_t *c, game_t *game, client_t *clients);

/**
 * @brief Destroy the server
 *
 * @param s the server structure
 */
void free_wifi(server_t *s);
