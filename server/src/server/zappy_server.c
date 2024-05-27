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
#include "args_info.h"

static void handle_cli_isset(server_t *serv, int i)
{
    if (serv->clients[i].fd != 0 &&
        FD_ISSET(serv->clients[i].fd, &serv->read_fds)) {
        if (read_client(&serv->clients[i]) == ERROR) {
            close_client(&serv->clients[i]);
        }
    }
}

static void handle_client(server_t *serv)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        handle_cli_isset(serv, i);
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
        line[strlen(line) - 1] = '\0';
        handle_server_cmd(line, serv);
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

static void exec_clients(server_t *s)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (s->clients[i].fd != 0 && s->clients[i].buffer.size > 0) {
            handle_buffer(&s->clients[i], &s->game);
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
    if (serv.fd == ERROR)
        return ERROR;
    logger_info("Server up and running on port %d\n", args->port);
    serv.game.map = create_map(args->width, args->height);
    fill_map(serv.game.map);
    while (!retval) {
        fill_fd_set(&serv);
        retval = select_server(&serv);
        exec_clients(&serv);
    }
    logger_info("Server shutting down\n");
    return SUCCESS;
}
