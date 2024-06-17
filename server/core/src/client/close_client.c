/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** close_client
*/

#include <stdio.h>
#include <unistd.h>

#include "core/client.h"
#include "core/types/buffer.h"
#include "core/types/client.h"
#include "utils.h"

void destroy_client(client_t *c)
{
    close(c->fd);
    str_free(c->io.res);
    str_free(c->io.req);
    for (size_t i = 0; c->commands && i < c->commands->size; i++)
        str_free(c->commands->data[i]);
    if (c->type == AI)
        destroy_ai(&c->ai);
    queue_destroy_queue_command_t(c->commands);
    va_free(2, c->address, c);
}

void close_client(client_t *c, struct client_list *clients)
{
    if (c->type == AI)
        broadcast_to(GUI, clients, "pdi %d\n", c->ai->id);
    destroy_client(c);
}
