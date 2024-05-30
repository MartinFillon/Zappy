/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** zappy_server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>

#include "client.h"
#include "macros.h"
#include "server.h"
#include "types/client.h"
#include "utils.h"
#include "zappy.h"
#include "args_info.h"
#include <bits/types/struct_timeval.h>

static void handle_cli_isset(zappy_t *z, int i)
{
    if (z->clients[i].fd != 0 &&
        FD_ISSET(z->clients[i].fd, &z->server.read_fds)) {
        if (read_client(&z->clients[i]) == ERROR) {
            close_client(&z->clients[i]);
        }
    }
}

static void handle_client(zappy_t *z)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        handle_cli_isset(z, i);
    }
}

static int select_server(zappy_t *z)
{
    struct timeval t = {0, 1};
    int retval =
        select(SOMAXCONN, &z->server.read_fds, &z->server.write_fds, NULL, &t);
    char *line = NULL;
    size_t n = 0;

    if (retval == -1)
        return SERV_END;
    if (FD_ISSET(0, &z->server.read_fds)) {
        if (getline(&line, &n, stdin) == -1)
            return SERV_END;
        line[strlen(line) - 1] = '\0';
        handle_server_cmd(line, z);
    }
    if (FD_ISSET(z->server.fd, &z->server.read_fds))
        accept_new_client(&z->server, z->clients);
    handle_client(z);
    return SUCCESS;
}

static void fill_fd_set(zappy_t *z)
{
    FD_ZERO(&z->server.read_fds);
    FD_ZERO(&z->server.write_fds);
    FD_SET(0, &z->server.read_fds);
    FD_SET(z->server.fd, &z->server.read_fds);
    for (int i = 0; i < SOMAXCONN; i++) {
        if (z->clients[i].fd != 0) {
            FD_SET(z->clients[i].fd, &z->server.read_fds);
        }
    }
}

static void exec_clients(zappy_t *z)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (z->clients[i].fd != 0 &&
            z->clients[i].buffer.size > 0) {
            handle_buffer(&z->clients[i], &z->game, z->clients);
        }
    }
}

static void check_eating(client_t *clients)
{
    for (__auto_type i = 0; i < SOMAXCONN; i++)
        if (clients[i].fd > 0 && clients[i].type == AI)
            make_ai_eat(&clients[i], clients, i);
}

int loop_server(args_infos_t *args)
{
    zappy_t z = {0};
    int retval = 0;

    if (init_program(args, &z))
        return ERROR;
    while (!retval) {
        fill_fd_set(&z);
        retval = select_server(&z);
        exec_clients(&z);
        check_eating(z.clients);
    }
    logger_info("Server shutting down\n");
    return SUCCESS;
}
