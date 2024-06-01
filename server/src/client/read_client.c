/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_client
*/

#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "macros.h"
#include "types/client.h"

int read_client(client_t *c)
{
    char buffer[BUFF_SIZE + 1] = {0};
    ssize_t bytes_read = 0;

    bytes_read = read(c->fd, buffer, BUFF_SIZE);
    if (bytes_read <= 0) {
        logs(INFO, "Client %d has disconnected\n", c->fd);
        return -1;
    }
    logs(DEBUG, "Read %ld bytes from client %d\n", bytes_read, c->fd);
    if (c->io.req.buffer == NULL) {
        c->io.req.buffer = strdup(buffer);
        c->io.req.size = strlen(c->io.req.buffer);
    } else {
        c->io.req.buffer =
            realloc(c->io.req.buffer, c->io.req.size + bytes_read + 1);
        strcat(c->io.req.buffer, buffer);
        c->io.req.size = strlen(c->io.req.buffer);
    }
    logs(DEBUG, "Buffer: %s\n", c->io.req.buffer);
    return 0;
}
