/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <string.h>

#include "core/server.h"
#include "core/types/client.h"
#include "logger.h"
#include "str.h"
#include "zappy.h"

static int one_line_case(client_t *c, struct vector_str_t *lines)
{
    queue_pushfront_queue_command_t(c->commands, lines->data[0]);
    str_clear(c->io.req);
    vec_destroy_vector_str_t(lines);
    return 0;
}

int handle_buffer(client_t *c, zappy_t *z)
{
    struct vector_str_t *lines = str_split(c->io.req, "\n");

    logs(DEBUG, "Client %d has %d lines in buffer\n", c->fd, lines->size);
    if (lines->size == 1)
        return one_line_case(c, lines);
    for (size_t i = 0; i < lines->size - 1; i++)
        queue_pushfront_queue_command_t(c->commands, lines->data[i]);
    str_free(c->io.req);
    c->io.req = lines->data[lines->size - 1];
    vec_destroy_vector_str_t(lines);
    return 0;
}
