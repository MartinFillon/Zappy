/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <stddef.h>
#include <string.h>

#include "core/client.h"
#include "core/gui/defs.h"
#include "core/middlewares.h"
#include "core/router/route.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/team.h"
#include "logger.h"
#include "str.h"

static void put_in_team(
    client_t *restrict c,
    game_t *game,
    size_t i,
    struct client_list *restrict clients
)
{
    logs(INFO, "Client %d is trying to be an AI\n", c->fd);
    if (init_ai(game, c, &game->teams->data[i], clients)) {
        prepare_response_cat(&c->io, "ko\n");
        logs(INFO, "No more eggs to place %d\n", c->fd);
        return;
    }
    c->type = AI;
    logs(INFO, "Client %d AI %d is ready\n", c->fd, c->ai->id);
}

static void send_eggs(client_t *c, team_t *team)
{
    for (__auto_type i = 0ul; i < team->eggs->size; i++)
        prepare_response_cat(
            &c->io,
            "smg eni %d %d %d\n",
            team->eggs->data[i]->id,
            team->eggs->data[i]->pos.x,
            team->eggs->data[i]->pos.y
        );
}

static void send_ais(client_t *c, ai_t *ai)
{
    prepare_response_cat(
        &c->io,
        "pnw %d %d %d %d %d %s\n",
        ai->id,
        ai->pos.x,
        ai->pos.y,
        ai->dir + 1,
        ai->level,
        ai->team->name
    );
}

static void init_gui(client_t *c, game_t *game, struct client_list *clients)
{
    command_state_t s = {NULL, clients, game};

    map_size(c, &s);
    request_time(c, &s);
    map_content_full(c, &s);
    team_names(c, &s);
    for (__auto_type i = 0ul; i < game->teams->size; i++)
        send_eggs(c, &game->teams->data[i]);
    for (__auto_type i = 0ul; i < game->ais->size; i++)
        send_ais(c, game->ais->data[i]);
}

void unset_command(client_t *c, command_state_t *s)
{
    if (strcmp(s->args->data[0]->data, "GRAPHIC") == 0) {
        c->type = GUI;
        init_gui(c, s->game, s->clients);
        return logs(INFO, "Client %d is a GUI\n", c->fd);
    }
    if (s->game->teams == NULL)
        return logs(WARNING, "No teams set\n");
    for (size_t i = 0; i < s->game->teams->size; i++)
        if (!strcmp(s->args->data[0]->data, s->game->teams->data[i].name)) {
            logs(
                INFO,
                "Client %d is an AI of team %s\n",
                c->fd,
                s->game->teams->data[i].name
            );
            return put_in_team(c, s->game, i, s->clients);
        }
    send_invalid_args(c);
}
