/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send
*/

#include <stdarg.h>
#include <stdio.h>
#include "core/types/client.h"

void send_client(client_t *client, char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vdprintf(client->fd, fmt, args);
    va_end(args);
}
