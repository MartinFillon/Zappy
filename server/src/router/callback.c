/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** callback
*/

#include "router/callbacks.h"
#include "router/route.h"
#include "types/client.h"
#include "types/game.h"

callback_t get_callback(char const * name)
{
    for (int i = 0; CALLBACKS[i].name; i++) {
        if (strcmp(CALLBACKS[i].name, name) == 0)
            return CALLBACKS[i].f;
    }
    return NULL;
}

void placeholder(
    char *,
    client_t *,
    game_t *,
    const client_t *
)
{
    return;
}
