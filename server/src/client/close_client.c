/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** close_client
*/

#include <unistd.h>
#include "client.h"
#include "types/client.h"

void close_client(client_t *c)
{
    close(c->fd);
    c->fd = 0;
    free(c->buffer.buffer);
    c->buffer.buffer = NULL;
    c->buffer.size = 0;
    c->ai = NULL;
    c->type = UNSET;
    c->entrypoint = &unset_entrypoint;
}
