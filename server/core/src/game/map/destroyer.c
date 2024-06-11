/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroyer
*/

#include <stdlib.h>

#include "core/types/map.h"
#include "utils.h"

void destroy_map(map_t *map)
{
    for (size_t i = 0; i < map->y; i++) {
        for (size_t j = 0; j < map->x; j++) {
            vec_destroy_vector_int(map->arena[i][j].players);
            free(map->arena[i][j].content);
        }
        free(map->arena[i]);
    }
    va_free(2, map->arena, map);
}
