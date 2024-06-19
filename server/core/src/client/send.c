/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send
*/

#include <stdarg.h>
#include <stdio.h>
#include "core/types/client.h"
#include "logger.h"

void send_client(client_t *client, char *fmt, ...)
{
    va_list args;
    va_list cpy;

    va_start(args, fmt);
    va_copy(cpy, args);
    // logs(DEBUG, "Client %d result buffer: ", client->fd);
    // vdprintf(2, fmt, args);
    vdprintf(client->fd, fmt, args);
    va_end(args);
    va_end(cpy);
}
