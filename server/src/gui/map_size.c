/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_size
*/

#include "client.h"

void map_size(
    char *args,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    (void) clients;
    if (cli->type != GUI)
        return;
    if (args[0] != '\0') {
        prepare_response(&cli->io, "sbp\n");
        return;
    }
    prepare_response(&cli->io, "msz %lu %lu\n", game->map->x, game->map->y);
}
