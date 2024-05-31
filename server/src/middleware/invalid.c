/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** invalid_args
*/

#include "types/client.h"
#include "router/error_callbacks.h"

void send_invalid_args(client_t *c)
{
    INVALID_ARGS_CALLBACKS[c->type](c->fd);
}

void send_unknown_command(client_t *c)
{
    UNKNOWN_CALLBACKS[c->type](c->fd);
}
