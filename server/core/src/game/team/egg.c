/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#include <stdlib.h>

#include "core/types/team.h"
#include "logger.h"

egg_t *create_egg(int x, int y)
{
    static int idx = 0;
    egg_t *egg = calloc(1, sizeof(egg_t));

    egg->id = idx;
    egg->pos.x = x;
    egg->pos.y = y;
    idx++;
    logs(INFO, "Created egg [%d] at %d %d\n", egg->id, x, y);
    return egg;
}

void destroy_egg(egg_t *egg)
{
    free(egg);
}
