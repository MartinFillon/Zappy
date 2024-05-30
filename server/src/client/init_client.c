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
    c->buffer.buffer = NULL;
    c->buffer.size = 0;
    c->ai = NULL;
    c->type = UNSET;
    // c->entrypoint = &unset_entrypoint;
}
