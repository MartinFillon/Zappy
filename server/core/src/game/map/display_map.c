/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_map
*/

#include <stdio.h>
#include <unistd.h>

#include "types/map.h"

void display_map(map_t *map, size_t y, size_t x)
{
    dprintf(STDOUT_FILENO, "TileMap info:\n");
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            dprintf(
                STDOUT_FILENO,
                "%d%c",
                map->arena[i][j].players->size != 0,
                j + 1 == x ? '\n' : ' '
            );
        }
    }
}
