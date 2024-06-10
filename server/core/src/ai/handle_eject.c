/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_eject
*/

#include <stdio.h>
#include <sys/socket.h>

#include "core/client.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/position.h"
#include "core/types/team.h"
#include "queue.h"
#include "utils.h"

static void eject_ai(client_t *this, client_t *oth, command_state_t *s)
{
    move_ai(oth->ai, this->ai->dir, s->game->map);
    broadcast_to(
        GUI,
        s->clients,
        "ppo %d %d %d %d\n",
        oth->ai->id,
        oth->ai->pos.x,
        oth->ai->pos.y,
        oth->ai->dir + 1
    );
}

static void loop_team_eggs(
    team_t *team,
    pos_t *this,
    struct client_list *clients,
    bool *has_ejected
)
{
    for (size_t i = 0; i < team->eggs->size; i++) {
        if (is_coord_equal(&team->eggs->data[i]->pos, this)) {
            broadcast_to(GUI, clients, "edi %d\n", team->eggs->data[i]->id);
            queue_erase_at_queue_egg_t(team->eggs, i);
            i--;
            *has_ejected = true;
        }
    }
}

static void destroy_common_eggs(
    game_t *game,
    pos_t *this,
    struct client_list *clients,
    bool *has_ejected
)
{
    for (size_t i = 0; i < game->teams->size; i++) {
        loop_team_eggs(&game->teams->data[i], this, clients, has_ejected);
    }
}

void handle_eject(client_t *cli, command_state_t *s)
{
    bool has_ejected = false;

    for (size_t i = 0; i < s->clients->size; i++) {
        if (cli->ai->id != s->clients->data[i].ai->id &&
            is_coord_equal(&cli->ai->pos, &s->clients->data[i].ai->pos)) {
            eject_ai(cli, &s->clients->data[i], s);
            prepare_response(
                &s->clients->data[i].io, "eject: %d\n", cli->ai->dir
            );
            has_ejected = true;
        }
    }
    destroy_common_eggs(s->game, &cli->ai->pos, s->clients, &has_ejected);
    prepare_response(&cli->io, "%s\n", (has_ejected ? "ok" : "ko"));
    if (has_ejected)
        broadcast_to(GUI, s->clients, "pex %d\n", cli->ai->id);
}
