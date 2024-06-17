/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** teleport
*/

#include "core/server.h"
#include "core/types/position.h"
#include "logger.h"
#include "zappy.h"

static bool get_pos(zappy_t *z, long id, pos_t *p)
{
    for (size_t i = 0; i < z->game.ais->size; i++) {
        if (z->game.ais->data[i]->id == id) {
            *p = z->game.ais->data[i]->pos;
            return true;
        }
    }
    return false;
}

static bool set_pos(zappy_t *z, long id, pos_t *p)
{
    for (size_t i = 0; i < z->game.ais->size; i++) {
        if (z->game.ais->data[i]->id == id) {
            z->game.ais->data[i]->pos = *p;
            return true;
        }
    }
    return false;
}

void teleport(zappy_t *z, struct vector_str_t *args)
{
    long id;
    long id2;
    pos_t p = {0};

    if (str_toint(&id, args->data[1]))
        return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
    if (str_toint(&id2, args->data[2]))
        return logs(
            ERROR_LEVEL, "The second argument must be an id of a player\n"
        );
    if (!get_pos(z, id2, &p))
        return logs(ERROR_LEVEL, "Player not found for id %d\n", id2);
    if (!set_pos(z, id, &p))
        return logs(ERROR_LEVEL, "Player not found for id %d\n", id);
}
