/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_client
*/

#include <string.h>

#include "core/client.h"
#include "core/types/client.h"

client_t *init_client(int fd, char *address, uint32_t port)
{
    client_t *c = calloc(1, sizeof(client_t));

    c->fd = fd;
    c->io.req.buffer = NULL;
    c->io.req.size = 0;
    c->io.res.buffer = NULL;
    c->io.res.size = 0;
    c->ai = NULL;
    c->type = UNSET;
    c->commands = queue_create_queue_command_t(10);
    c->address = strdup(address);
    c->port = port;
    return c;
}
