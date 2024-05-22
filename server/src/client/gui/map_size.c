/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_size
*/

#include <stdio.h>

#include "types/client.h"

void map_size(char *args, client_t *cli, game_t *game)
{
    if (cli->type != GUI)
        return;
    if (args[0] != '\0') {
        dprintf(cli->fd, "sbp\n");
        return;
    }
    dprintf(cli->fd, "msz %lu %lu\n", game->map->x, game->map->y);
}
