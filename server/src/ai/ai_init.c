/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include "server.h"
#include "types/ai.h"
#include "types/client.h"

bool init_ai(game_t *game, client_t *client)
{
    if (game->ais->len + 1 > game->ais->size) {
        if (resize_vector_ai(game->ais))
            return true;
    }
}
