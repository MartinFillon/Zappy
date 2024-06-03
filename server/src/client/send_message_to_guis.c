/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** send_message_to_guis
*/

#include <stdarg.h>
#include <sys/socket.h>

#include "client.h"

void broadcast_to(enum client_type_e type, client_t *clients, char *fmt, ...)
{
    va_list va;
    va_list tmp;

    va_start(va, fmt);
    for (size_t i = 0ul; i < SOMAXCONN; i++)
        if (clients[i].type == type) {
            va_copy(tmp, va);
            prepare_response_cat_va(&clients[i].io, fmt, tmp);
            va_end(tmp);
        }
    va_end(va);
}
