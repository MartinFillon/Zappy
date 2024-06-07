/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** godmode
*/

#include "client.h"
#include "logger.h"
#include "server.h"
#include "str.h"
#include "types/ai.h"
#include "types/object.h"
#include "zappy.h"

static void try_give_object(zappy_t *z, ai_t *ai, str_t *obj, long count)
{
    int i = 0;

    for (; i < NB_OBJ; i++) {
        if (!strcasecmp(obj->data, all_obj[i].name)) {
            break;
        }
    }
    if (i == NB_OBJ)
        return logs(ERROR_LEVEL, "Second argument is an unknown object\n");
    ai->inventory[all_obj[i].obj] += count;
    logs(INFO, "Gave %ld of %s\n", count, all_obj[i].name);
    broadcast_to(
        GUI, z->clients, "pin %lu %ld %ld", ai->id, ai->pos.x, ai->pos.y
    );
    for (size_t i = FOOD; i < OBJ_COUNT; i++)
        broadcast_to(GUI, z->clients, " %lu", ai->inventory[i]);
    broadcast_to(GUI, z->clients, "\n");
}

void give(zappy_t *z, struct vector_str_t *args)
{
    long id;
    long count;

    if (str_toint(&id, args->data[1]))
        return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
    if (str_toint(&count, args->data[3]))
        return logs(ERROR_LEVEL, "Thrid argument must be a number\n");
    for (size_t i = 0; i < z->clients->size; i++) {
        if (z->game.ais->data[i].id == id) {
            return try_give_object(
                z, &z->game.ais->data[i], args->data[2], count
            );
        }
    }
    return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
}
