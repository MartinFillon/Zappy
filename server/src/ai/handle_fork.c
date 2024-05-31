/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_fork
*/

#include <stdio.h>
#include "logger.h"
#include "types/team.h"
#include "utils.h"
#include "types/client.h"
#include "client.h"

void handle_fork(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    egg_t *egg = NULL;

    (void) clients;
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    egg = create_egg(game->map->x, game->map->y);
    if (!egg) {
        logs(ERROR_LEVEL, "Allocation error on fork handling");
        return;
    }
    queue_pushback_queue_egg_t(cli->ai->team->eggs, egg);
    prepare_response(&cli->io, "ok\n");
}
