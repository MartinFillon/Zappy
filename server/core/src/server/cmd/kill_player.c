/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_kill_player
*/

#include <stdio.h>
#include "logger.h"
#include "str.h"
#include "zappy.h"

void handle_kill_player(zappy_t *z, struct vector_str_t *args)
{
    long id = 0;
    struct client_list *clients = z->clients;

    if (str_toint(&id, args->data[1]))
        return logs(ERROR_LEVEL, "Argument must be an id of a player\n");
    for (size_t i = 0; i < clients->size; i++)
        if (clients->data[i]->type == AI && clients->data[i]->ai->id == id) {
            kill_ai(clients, z->game.ais, i);
            logs(INFO, "Ai with id [%d] was killed\n", id);
            return;
        }
}
