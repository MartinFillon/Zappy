/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** verif_tile_requirement
*/

#include <stdbool.h>
#include <stdlib.h>
#include "core/types/object.h"

bool verif_tile_requirement(size_t *con, const size_t *tile)
{
    for (size_t i = LINEMATE; i < OBJ_COUNT; i++)
        if (!(con[i] >= tile[i]))
            return false;
    return true;
}
