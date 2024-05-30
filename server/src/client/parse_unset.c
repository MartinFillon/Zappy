/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <stddef.h>
#include <string.h>

#include "client.h"
#include "gui/defs.h"
#include "logger.h"
#include "macros.h"
#include "types/client.h"
#include "types/game.h"
#include "types/team.h"

static int put_in_team(client_t *c, game_t *game, size_t i)
{
    logs(INFO, "Client %d is trying to be an AI\n", c->fd);
    c->type = AI;
    // c->entrypoint = &ai_entrypoint;
    if (init_ai(game, c, &game->teams->data[i])) {
        send_client(c, "ko\n");
        logs(INFO, "No more eggs to place %d\n", c->fd);
        return ERROR;
    }
    logs(INFO, "AI inited\n");
    return SUCCESS;
}

static void send_eggs(client_t *c, team_t *team)
{
    for (__auto_type i = 0ul; i < team->eggs->size; i++)
        send_client(
            c,
            "smg eni %d %d %d\n",
            team->eggs->data[i]->id,
            team->eggs->data[i]->pos.x,
            team->eggs->data[i]->pos.y
        );
}

static void send_ais(client_t *c, ai_t *ai)
{
    send_client(
        c,
        "pnw %d %d %d %d %d %s\n",
        ai->id,
        ai->pos.x,
        ai->pos.y,
        ai->dir + 1,
        ai->level,
        ai->team->name
    );
}

static int init_gui(client_t *c, game_t *game, client_t *clients)
{
    map_size("", c, game, clients);
    request_time("", c, game, clients);
    map_content_full("", c, game, clients);
    team_names("", c, game, clients);
    for (__auto_type i = 0ul; i < game->teams->size; i++)
        send_eggs(c, &game->teams->data[i]);
    for (__auto_type i = 0ul; i < game->ais->size; i++)
        send_ais(c, &game->ais->data[i]);
    return 0;
}

int unset_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    (void)clients;
    if (strcmp(line, "GRAPHIC") == 0) {
        logs(INFO, "Client %d is a GUI\n", c->fd);
        c->type = GUI;
        // c->entrypoint = &gui_entrypoint;
        vec_pushback_vector_int(game->guis, c->fd);
        return init_gui(c, game, clients);
    }
    if (game->teams == NULL) {
        logs(WARNING, "No teams set\n");
        return 1;
    }
    for (size_t i = 0; i < game->teams->size; i++)
        if (strcmp(line, game->teams->data[i].name) == 0)
            return put_in_team(c, game, i);
    send_client(c, "ko\n");
    return ERROR;
}
