/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <string.h>

#include "logger.h"
#include "server.h"
#include "types/client.h"
#include "utils.h"

static int handle_buffer_internal(
    size_t idx,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    char *tmp = strdup(c->io.req.buffer + idx + 1);
    char *com = strndup(c->io.req.buffer, idx);

    if (!tmp || !com) {
        va_free(2, tmp, com);
        return 1;
    }
    free(c->io.req.buffer);
    c->io.req.buffer = tmp;
    c->io.req.size = strlen(tmp);
    logs(INFO, "Client %d sent command: %s\n", c->fd, com);
    c->entrypoint(com, c, game, clients);
    return handle_buffer(c, game, clients);
}

int handle_buffer(client_t *c, game_t *game, client_t *clients)
{
    size_t idx = (size_t)(strstr(c->io.req.buffer, "\n") - c->io.req.buffer);

    if (idx > c->io.req.size)
        return 1;
    return handle_buffer_internal(idx, c, game, clients);
}
