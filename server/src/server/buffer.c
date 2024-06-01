/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <string.h>

#include "logger.h"
#include "router/router.h"
#include "server.h"
#include "str.h"
#include "types/client.h"
#include "utils.h"
#include "zappy.h"

static int handle_buffer_internal(size_t idx, client_t *c, zappy_t *z)
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
    queue_pushback_queue_command_t(c->commands, str_snew(com));
    return handle_buffer(c, z);
}

int handle_buffer(client_t *c, zappy_t *z)
{
    size_t idx = (size_t)(strstr(c->io.req.buffer, "\n") - c->io.req.buffer);

    if (idx > c->io.req.size)
        return 1;
    return handle_buffer_internal(idx, c, z);
}
