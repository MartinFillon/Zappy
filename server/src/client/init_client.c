/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_client
*/

#include "client.h"

void init_client(client_t *c, int fd)
{
    c->fd = fd;
    c->io.req.buffer = NULL;
    c->io.req.size = 0;
    c->io.res.buffer = NULL;
    c->io.res.size = 0;
    c->ai = NULL;
    c->type = UNSET;
    c->commands = queue_create_queue_command_t(10);
}
