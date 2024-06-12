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
#include "macros.h"
#include "zappy.h"

static void handle_client_closing(zappy_t *z, int i)
{
    if (z->clients->data[i].type != AI) {
        close_client(&z->clients->data[i], z->clients);
        vec_erase_at_client_list(z->clients, i);
    } else {
        kill_ai(z->clients, z->game.ais, i);
    }
}

static void handle_cli_isset(zappy_t *z, int i)
{
    if (FD_ISSET(z->clients->data[i].fd, &z->server.read_fds))
        if (read_client(&z->clients->data[i]) == ERROR)
            handle_client_closing(z, i);
    if (FD_ISSET(z->clients->data[i].fd, &z->server.write_fds) &&
        z->clients->data[i].io.is_ready) {
        z->clients->data[i].io.is_ready = false;
        if (z->clients->data[i].io.res.size != 0 &&
            z->clients->data[i].io.res.buffer != NULL) {
            send_client(
                &z->clients->data[i], z->clients->data[i].io.res.buffer
            );
            free_buffer(&z->clients->data[i].io.res);
        }
    }
}

static void handle_client(zappy_t *z)
{
    size_t size = z->clients->size;

    for (size_t i = 0; i < size; i++) {
        handle_cli_isset(z, i);
    }
}

static int get_max_fd(struct client_list *list)
{
    int mx = 0;

    for (size_t i = 0; i < list->size; i++)
        mx = MAX(list->data[i].fd, mx);
    return mx;
}

int select_server(zappy_t *z)
{
    struct timeval t = {0, 1};
    int nfd = get_max_fd(z->clients);
    int retval =
        select(nfd, &z->server.read_fds, &z->server.write_fds, NULL, &t);
    char *line = NULL;
    size_t n = 0;

    if (retval == -1 && errno == EINTR)
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

void fill_fd_set(zappy_t *z)
{
    FD_ZERO(&z->server.read_fds);
    FD_ZERO(&z->server.write_fds);
    FD_SET(0, &z->server.read_fds);
    FD_SET(z->server.fd, &z->server.read_fds);
    for (size_t i = 0; i < z->clients->size; i++) {
        FD_SET(z->clients->data[i].fd, &z->server.read_fds);
        if (z->clients->data[i].io.is_ready) {
            FD_SET(z->clients->data[i].fd, &z->server.write_fds);
        }
    }
}

void exec_clients(zappy_t *z)
{
    for (size_t i = 0; i < z->clients->size; i++) {
        if (z->clients->data[i].io.req.size > 0) {
            handle_buffer(&z->clients->data[i], z);
        }
    }
    execute_commands(z);
}

void check_eating(struct client_list *clients)
{
    for (size_t i = 0; i < clients->size; i++)
        if (clients->data[i].type == AI)
            make_ai_eat(&clients->data[i], clients, i);
}

void kill_dead_ais(struct client_list *clients, struct vector_ai_t *ais)
{
    size_t size = clients->size;

    for (size_t i = 0; i < size; i++)
        if (clients->data[i].type == AI &&
            clients->data[i].ai->alive == false) {
            kill_ai(clients, ais, i);
        }
}
