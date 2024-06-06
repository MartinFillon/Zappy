/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_rotate
*/

#include <stdbool.h>

#include "client.h"
#include "router/route.h"
#include "types/ai.h"
#include "types/client.h"
#include "utils.h"

void handle_rotate_right(client_t *cli, command_state_t *s)
{
    cli->ai->dir = (cli->ai->dir + 1) % NB_DIR;
    prepare_response_cat(&cli->io, "ok\n");
    broadcast_to(
        GUI,
        s->clients,
        "ppo %d %d %d %d\n",
        cli->ai->id,
        cli->ai->pos.x,
        cli->ai->pos.y,
        cli->ai->dir + 1
    );
}

void handle_rotate_left(client_t *cli, command_state_t *s)
{
    (void)s;
    cli->ai->dir = modulo((cli->ai->dir - 1), NB_DIR);
    prepare_response_cat(&cli->io, "ok\n");
    broadcast_to(
        GUI,
        s->clients,
        "ppo %d %d %d %d\n",
        cli->ai->id,
        cli->ai->pos.x,
        cli->ai->pos.y,
        cli->ai->dir + 1
    );
}
