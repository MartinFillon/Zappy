/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_eject
*/

#include <stdio.h>
#include <sys/socket.h>

#include "queue.h"
#include "types/ai.h"
#include "types/client.h"
#include "client.h"
#include "types/game.h"
#include "types/position.h"
#include "types/team.h"
#include "utils.h"

static void eject_ai(client_t *this, client_t *oth, game_t *game)
{
    move_ai(oth->ai, this->ai->dir, game->map);
}

static void loop_team_eggs(team_t *team, pos_t *this)
{
    for (size_t i = 0; i < team->eggs->size; i++) {
        if (is_coord_equal(&team->eggs->data[i]->pos, this)) {
            queue_erase_at_queue_egg_t(team->eggs, i);
            i--;
        }
    }
}

static void destroy_common_eggs(game_t *game, pos_t *this)
{
    for (size_t i = 0; i < game->teams->size; i++) {
        loop_team_eggs(&game->teams->data[i], this);
    }
}

void handle_eject(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    for (size_t i = 0; i < SOMAXCONN; i++) {
        if (clients[i].fd != 0 && cli->ai->id != clients[i].ai->id
            && is_coord_equal(&cli->ai->pos, &clients[i].ai->pos)) {
            eject_ai(cli, &clients[i], game);
            prepare_response(&clients[i].io, "eject: %d\n", cli->ai->dir);
        }
    }
    destroy_common_eggs(game, &cli->ai->pos);
    prepare_response(&cli->io, "ok\n");
}
