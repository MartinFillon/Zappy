/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_fork
*/

#include "logger.h"
#include "router/route.h"
#include "types/team.h"
#include "types/client.h"
#include "client.h"

void handle_fork(client_t *cli, command_state_t *s)
{
    egg_t *egg = create_egg(s->game->map->x, s->game->map->y);

    if (!egg) {
        logs(ERROR_LEVEL, "Allocation error on fork handling");
        return;
    }
    egg->pos.x = cli->ai->pos.x;
    egg->pos.y = cli->ai->pos.y;
    queue_pushback_queue_egg_t(cli->ai->team->eggs, egg);
    prepare_response(&cli->io, "ok\n");
}
