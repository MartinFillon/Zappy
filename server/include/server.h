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
#include "args_info.h"

typedef struct server_s {
    int fd;
    fd_set read_fds;
    fd_set write_fds;

    client_t clients[SOMAXCONN];
} server_t;

int server_init(uint32_t port);
int loop_server(args_infos_t *args);
int accept_new_client(server_t *s);
int handle_buffer(client_t *c, game_t *game);
