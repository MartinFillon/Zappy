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

#include "core/client.h"
#include "core/types/game.h"
#include "args_info.h"

typedef struct router_s router_t;
typedef struct zappy_s zappy_t;

typedef struct server_s {
    int fd;
    fd_set read_fds;
    fd_set write_fds;
    router_t *router;
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
int accept_new_client(server_t *s, struct client_list *clients);

/**
 * @brief Handle the buffer
 *
 * @param c the client structure
 * @param z The zappy
 * @return int 0 if success, 84 if error
 */
int handle_buffer(client_t *c, zappy_t *z);

/**
 * @brief Destroy the server
 *
 * @param s the server structure
 */
void free_wifi(server_t *s);

void execute_commands(zappy_t *z);
int select_server(zappy_t *z);
void fill_fd_set(zappy_t *z);
void exec_clients(zappy_t *z);
void check_eating(struct client_list *clients);
void kill_dead_ais(struct client_list *clients, struct vector_ai_t *ais);
void refill_map(game_t *game);