/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** close_client
*/

#include <unistd.h>
#include "client.h"
#include "queue.h"
#include "types/client.h"

void free_buffer(struct buffer_s *buffer)
{
    free(buffer->buffer);
    buffer->buffer = NULL;
    buffer->size = 0;
}

void close_client(client_t *c, client_t *clients)
{
    if (c->type == AI)
        broadcast_to(GUI, clients, "pdi %d\n", c->ai->id);
    close(c->fd);
    c->fd = 0;
    free_buffer(&c->io.req);
    free_buffer(&c->io.res);
    c->ai = NULL;
    c->type = UNSET;
    for (size_t i = 0; i < c->commands->size; i++)
        str_free(c->commands->data[i]);
    queue_destroy_queue_command_t(c->commands);
}
