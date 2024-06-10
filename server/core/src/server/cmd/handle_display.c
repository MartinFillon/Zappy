/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_map
*/

#include <unistd.h>

#include "core/map.h"
#include "core/types/map.h"
#include "zappy.h"

void handle_display_map(zappy_t *serv, struct vector_str_t *args)
{
    map_t *map = serv->game.map;

    (void)args;
    display_map(map, map->y, map->x);
}
