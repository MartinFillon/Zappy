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
    fd_set except_fds;
    router_t *router;
    sigset_t sig;
    bool docker;
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
 * @return int 0 if success, 84 if error
 */
int handle_buffer(client_t *c);

/**
 * @brief Destroy the server
 *
 * @param s the server structure
 */
void free_wifi(server_t *s);

/**
 * @brief execute the commands from stdin
 * @param z the zappy with all the data
 */
void execute_commands(zappy_t *z);

/**
 * @brief call select on the server
 * @param z the zappy with all the data
 */
int select_server(zappy_t *z);

/**
 * @brief fills the fd_sets with the clients fd
 * @param z the zappy with all the data
 */
void fill_fd_set(zappy_t *z);

/**
 * @brief execute the commands in the client buffers
 * @param z the zappy with all the data
 */
void exec_clients(zappy_t *z);

/**
 * @brief check if the client needs to eat and make him eat
 * @param clients the clients list to check
 */
void check_eating(struct client_list *clients);

/**
 * @brief check if the client is dead and kill him
 * @param clients the clients list to check
 */
void kill_dead_ais(struct client_list *clients, struct vector_ai_t *ais);

/**
 * @brief refill the map with the resources
 * @param game the game structure
 */
void refill_map(game_t *game);
