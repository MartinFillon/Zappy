/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#include <stdlib.h>

#include "types/team.h"

egg_t *create_egg(int width, int height)
{
    static int idx = 0;
    egg_t *egg = calloc(1, sizeof(egg_t));

    egg->id = idx;
    egg->pos.x = rand() % width;
    egg->pos.y = rand() % height;
    idx++;
    return egg;
}

void destroy_egg(egg_t *egg)
{
    free(egg);
}
