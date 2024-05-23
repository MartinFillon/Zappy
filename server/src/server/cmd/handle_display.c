/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_map
*/

#include <unistd.h>
#include "server.h"
#include "types/client.h"

#include "map.h"
#include "types/map.h"

void handle_display_map(server_t *serv)
{
    map_t *map = serv->game.map;

    display_map(map, map->y, map->x);
}
