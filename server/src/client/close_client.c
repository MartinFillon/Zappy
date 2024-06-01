/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** close_client
*/

#include <unistd.h>
#include "client.h"
#include "types/client.h"

void free_buffer(struct buffer_s *buffer)
{
    free(buffer->buffer);
    buffer->buffer = NULL;
    buffer->size = 0;
}

void close_client(client_t *c)
{
    close(c->fd);
    c->fd = 0;
    free_buffer(&c->io.req);
    free_buffer(&c->io.res);
    c->ai = NULL;
    c->type = UNSET;
}
