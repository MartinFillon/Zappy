/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#include <stdlib.h>

#include "types/team.h"
#include "utils.h"
#include "args_info.h"

egg_t *create_egg(args_infos_t *args)
{
    static int idx = 0;
    egg_t *egg = calloc(1, sizeof(egg_t));

    egg->id = idx;
    egg->pos.x = rand() % args->width;
    egg->pos.y = rand() % args->height;
    logger_info("Spawned egg %d at %d %d\n", idx, egg->pos.x, egg->pos.y);
    idx++;
    return egg;
}
