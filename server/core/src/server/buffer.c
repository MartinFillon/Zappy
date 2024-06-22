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

static int one_line_case(client_t *c, struct vector_str_t *lines)
{
    queue_pushback_queue_command_t(c->commands, lines->data[0]);
    str_clear(c->io.req);
    vec_destroy_vector_str_t(lines);
    return 0;
}

int handle_buffer(client_t *c)
{
    struct vector_str_t *lines = str_split(c->io.req, "\n");
    bool is_last_line = c->io.req->data[c->io.req->size - 1] == '\n' ||
        c->io.req->data[c->io.req->size] == '\n';

    logs(DEBUG, "Client %d has %d lines in buffer\n", c->fd, lines->size);
    if (lines->size == 0) {
        vec_destroy_vector_str_t(lines);
        return 0;
    }
    for (size_t i = 0; i < lines->size; i++)
        logs(DEBUG, "Line %d: %s\n", i, lines->data[i]->data);
    if (lines->size == 1)
        return one_line_case(c, lines);
    for (int i = 0; i < (int)lines->size - !is_last_line; i++)
        queue_pushback_queue_command_t(c->commands, lines->data[i]);
    str_free(c->io.req);
    c->io.req = !is_last_line ? lines->data[lines->size - 1] : str_new(1024);
    vec_destroy_vector_str_t(lines);
    return 0;
}
