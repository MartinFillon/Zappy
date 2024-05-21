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
#include "define.h"
#include "server.h"
#include "utils.h"

static void handle_client(server_t *serv)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (serv->clients[i].fd != 0 &&
            FD_ISSET(serv->clients[i].fd, &serv->read_fds)) {
            if (read_client(&serv->clients[i]) == ERROR) {
                close_client(&serv->clients[i]);
            }
        }
    }
}

/// @brief Actually there is only stdin that is read so we put 1 to maxfd.
static int select_server(server_t *serv)
{
    int retval =
        select(SOMAXCONN, &serv->read_fds, &serv->write_fds, NULL, NULL);
    char *line = NULL;
    size_t n = 0;

    if (retval == -1)
        return SERV_END;
    if (FD_ISSET(0, &serv->read_fds)) {
        if (getline(&line, &n, stdin) == -1)
            return SERV_END;
        dprintf(1, "%s", line);
    }
    if (FD_ISSET(serv->fd, &serv->read_fds))
        accept_new_client(serv);
    handle_client(serv);
    return SUCCESS;
}

static void fill_fd_set(server_t *serv)
{
    FD_ZERO(&serv->read_fds);
    FD_ZERO(&serv->write_fds);
    FD_SET(0, &serv->read_fds);
    FD_SET(serv->fd, &serv->read_fds);
    for (int i = 0; i < SOMAXCONN; i++) {
        if (serv->clients[i].fd != 0) {
            FD_SET(serv->clients[i].fd, &serv->read_fds);
        }
    }
}

int loop_server(args_infos_t *args)
{
    server_t serv = {0};
    int retval = 0;

    logger_info("Starting server on port %d\n", args->port);
    serv.game.teams = args->names;
    serv.fd = server_init(args->port);
    logger_info("Server up and running on port %d\n", args->port);
    if (serv.fd == ERROR)
        return ERROR;
    while (!retval) {
        fill_fd_set(&serv);
        retval = select_server(&serv);
    }
    logger_info("Server shutting down\n");
    return SUCCESS;
}