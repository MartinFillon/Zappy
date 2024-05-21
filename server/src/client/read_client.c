/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** read_client
*/

#include <string.h>
#include <unistd.h>

#include "macros.h"
#include "types/client.h"
#include "utils.h"

int read_client(client_t *c)
{
    char buffer[BUFF_SIZE + 1] = {0};
    ssize_t bytes_read = 0;

    bytes_read = read(c->fd, buffer, BUFF_SIZE);
    if (bytes_read <= 0) {
        logger_info("Client %d has disconnected\n", c->fd);
        return -1;
    }
    logger_debug("Read %ld bytes from client %d\n", bytes_read, c->fd);
    if (c->buffer.buffer == NULL) {
        c->buffer.buffer = strdup(buffer);
        c->buffer.size = strlen(c->buffer.buffer);
    } else {
        c->buffer.buffer =
            realloc(c->buffer.buffer, c->buffer.size + bytes_read + 1);
        strcat(c->buffer.buffer, buffer);
        c->buffer.size = strlen(c->buffer.buffer);
    }
    return 0;
}
