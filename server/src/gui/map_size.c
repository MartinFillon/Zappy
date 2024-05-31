/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_size
*/

#include "client.h"
#include "gui/defs.h"

void map_size(client_t *cli, command_state_t *com)
{
    send_client(cli, "msz %lu %lu\n", com->game->map->x, com->game->map->y);
}
