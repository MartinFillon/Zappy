/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** zappy_server
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/types/struct_timeval.h>

#include "core/client.h"
#include "core/server.h"
#include "core/types/client.h"
#include "logger.h"
#include "macros.h"
#include "str.h"
#include "zappy.h"

static void handle_client_closing(zappy_t *z, int i)
{
    if (z->clients->data[i]->type != AI) {
        close_client(z->clients->data[i], z->clients);
        vec_erase_at_client_list(z->clients, i);
    } else {
        logs(
            INFO,
            "Killing ai %d due to deconnection\n",
            z->clients->data[i]->ai->id
        );
        kill_ai(z->clients, z->game.ais, i);
    }
}

static void handle_cli_isset(zappy_t *z, int i)
{
    client_t *self = z->clients->data[i];

    if (FD_ISSET(self->fd, &z->server.read_fds))
        if (read_client(self) == ERROR)
            return handle_client_closing(z, i);
    if (FD_ISSET(self->fd, &z->server.write_fds) && self->io.is_ready) {
        self->io.is_ready = false;
        if (self->io.res->size != 0 && self->io.res != NULL) {
            send_client(self, self->io.res->data);
            str_clear(self->io.res);
        }
    }
}

static void handle_client(zappy_t *z)
{
    for (size_t i = 0; i < z->clients->size; i++) {
        handle_cli_isset(z, i);
    }
}

int select_server(zappy_t *z)
{
    struct timeval t = {0, 1};
    int retval =
        select(MAXFD, &z->server.read_fds, &z->server.write_fds, NULL, &t);
    char *line = NULL;
    size_t n = 0;

    if (retval == -1 && errno == EINTR)
        return SERV_END;
    if (FD_ISSET(STDIN_FILENO, &z->server.read_fds)) {
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

void fill_fd_set(zappy_t *z)
{
    FD_ZERO(&z->server.read_fds);
    FD_ZERO(&z->server.write_fds);
    FD_SET(0, &z->server.read_fds);
    FD_SET(z->server.fd, &z->server.read_fds);
    for (size_t i = 0; i < z->clients->size; i++) {
        FD_SET(z->clients->data[i]->fd, &z->server.read_fds);
        if (z->clients->data[i]->io.is_ready) {
            FD_SET(z->clients->data[i]->fd, &z->server.write_fds);
        }
    }
}

void exec_clients(zappy_t *z)
{
    for (size_t i = 0; i < z->clients->size; i++) {
        if (z->clients->data[i]->io.req->size > 0) {
            handle_buffer(z->clients->data[i]);
        }
    }
    execute_commands(z);
}

void check_eating(struct client_list *clients)
{
    for (size_t i = 0; i < clients->size; i++)
        if (clients->data[i]->type == AI)
            make_ai_eat(clients->data[i], clients);
}

void kill_dead_ais(struct client_list *clients, struct vector_ai_t *ais)
{
    for (size_t i = 0; i < clients->size; i++)
        if (clients->data[i]->type == AI &&
            clients->data[i]->ai->alive == false) {
            kill_ai(clients, ais, i);
        }
}
