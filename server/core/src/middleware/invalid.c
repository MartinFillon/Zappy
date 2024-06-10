/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** invalid_args
*/

#include "logger.h"
#include "types/client.h"
#include "router/error_callbacks.h"

static char *mode_to_str(enum client_type_e mode)
{
    if (mode == GUI)
        return "GUI";
    if (mode == AI)
        return "AI";
    return "UNSET";
}

void send_invalid_args(client_t *c)
{
    logs(
        INFO,
        "Client %d of type %s sent a command with invalid arguments",
        c->fd,
        mode_to_str(c->type)
    );
    INVALID_ARGS_CALLBACKS[c->type](c);
}

void send_unknown_command(client_t *c)
{
    logs(
        INFO,
        "Client %d of type %s sent an unknown command",
        c->fd,
        mode_to_str(c->type)
    );
    UNKNOWN_CALLBACKS[c->type](c);
}
