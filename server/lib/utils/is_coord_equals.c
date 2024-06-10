/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_coord_equals
*/

#include <stdbool.h>

#include "types/position.h"

bool is_coord_equal(pos_t *this, pos_t *oth)
{
    return this->x == oth->x && this->y == oth->y;
}
