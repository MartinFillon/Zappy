/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroyer
*/

#include "types/map.h"

void destroy_map(map_t *map)
{
    for (size_t i = 0; i < map->x; i++) {
        free(map->arena[i]);
    }
    free(map);
}
