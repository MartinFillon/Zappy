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
#include "map.h"
#include "server.h"
#include "utils.h"
#include "zappy.h"
#include "args_info.h"

static void handle_cli_isset(zappy_t *z, int i)
{
    if (z->server.clients[i].fd != 0 &&
        FD_ISSET(z->server.clients[i].fd, &z->server.read_fds)) {
        if (read_client(&z->server.clients[i]) == ERROR) {
            close_client(&z->server.clients[i]);
        }
    }
}

static void handle_client(zappy_t *z)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        handle_cli_isset(z, i);
    }
}

/// @brief Actually there is only stdin that is read so we put 1 to maxfd.
static int select_server(zappy_t *z)
{
    int retval = select(
        SOMAXCONN, &z->server.read_fds, &z->server.write_fds, NULL, NULL
    );
    char *line = NULL;
    size_t n = 0;

    if (retval == -1)
        return SERV_END;
    if (FD_ISSET(0, &z->server.read_fds)) {
        if (getline(&line, &n, stdin) == -1)
            return SERV_END;
        dprintf(1, "%s", line);
    }
    if (FD_ISSET(z->server.fd, &z->server.read_fds))
        accept_new_client(&z->server);
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
        if (z->server.clients[i].fd != 0) {
            FD_SET(z->server.clients[i].fd, &z->server.read_fds);
        }
    }
}

static void exec_clients(zappy_t *z)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (z->server.clients[i].fd != 0 &&
            z->server.clients[i].buffer.size > 0) {
            handle_buffer(&z->server.clients[i], &z->game);
        }
    }
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
    }
    logger_info("Server shutting down\n");
    return SUCCESS;
}
