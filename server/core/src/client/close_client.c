/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** close_client
*/

#include <unistd.h>
#include "core/client.h"
#include "core/types/client.h"
#include "queue.h"

void free_buffer(struct buffer_s *buffer)
{
    free(buffer->buffer);
    buffer->buffer = NULL;
    buffer->size = 0;
}

void destroy_client(client_t *c)
{
    close(c->fd);
    c->fd = 0;
    free_buffer(&c->io.req);
    free_buffer(&c->io.res);
    c->ai = NULL;
    c->type = UNSET;
    for (size_t i = 0; i < c->commands->size; i++)
        str_free(c->commands->data[i]);
    queue_destroy_queue_command_t(c->commands);
    free(c->address);
    c->address = NULL;
}

void close_client(client_t *c, struct client_list *clients)
{
    if (c->type == AI)
        broadcast_to(GUI, clients, "pdi %d\n", c->ai->id);
    destroy_client(c);
}
