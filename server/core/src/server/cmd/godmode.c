/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** godmode
*/

#include "logger.h"
#include "str.h"
#include "zappy.h"

void godmode(zappy_t *z, struct vector_str_t *args)
{
    long id;

    if (str_toint(&id, args->data[1]))
        return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
    for (size_t i = 0; i < z->clients->size; i++) {
        if (z->game.ais->data[i]->id == id &&
            z->game.ais->data[i]->godmode == false) {
            logs(INFO, "Ai with id [%d] entered godmode\n", id);
            z->game.ais->data[i]->godmode = true;
            return;
        }
        if (z->game.ais->data[i]->id == id && z->game.ais->data[i]->godmode) {
            logs(INFO, "Ai with id [%d] quitted godmode\n", id);
            z->game.ais->data[i]->godmode = false;
            return;
        }
    }
    return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
}
