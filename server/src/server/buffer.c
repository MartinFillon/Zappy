/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <string.h>

#include "server.h"
#include "types/client.h"
#include "utils.h"

static int handle_buffer_internal(size_t idx, client_t *c, game_t *game)
{
    char *tmp = strdup(c->buffer.buffer + idx + 1);
    char *com = strndup(c->buffer.buffer, idx);

    if (!tmp || !com) {
        va_free(2, tmp, com);
        return 1;
    }
    free(c->buffer.buffer);
    c->buffer.buffer = tmp;
    c->buffer.size = strlen(tmp);
    logger_info("Client %d sent command: %s\n", c->fd, com);
    c->entrypoint(com, c, game);
    return handle_buffer(c, game);
}

int handle_buffer(client_t *c, game_t *game)
{
    size_t idx = (size_t)(strstr(c->buffer.buffer, "\n") - c->buffer.buffer);

    if (idx > c->buffer.size)
        return 1;
    return handle_buffer_internal(idx, c, game);
}
