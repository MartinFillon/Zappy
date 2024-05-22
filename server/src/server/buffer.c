/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <string.h>

#include "types/client.h"
#include "utils.h"

int handle_buffer(client_t *c, game_t *game)
{
    size_t idx = (size_t)(strstr(c->buffer.buffer, "\n") - c->buffer.buffer);
    char *tmp = strdup(c->buffer.buffer + idx + 2);
    char *com = strndup(c->buffer.buffer, idx);

    if (!tmp || !com) {
        va_free(2, tmp, com);
        return 1;
    }
    free(c->buffer.buffer);
    c->buffer.buffer = tmp;
    c->buffer.size = strlen(tmp);
    c->entrypoint(com, c, game);
    return 0;
}
