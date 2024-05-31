/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <stddef.h>
#include <string.h>

#include "logger.h"
#include "middlewares.h"
#include "router/route.h"
#include "types/client.h"
#include "types/game.h"
#include "types/team.h"

// static int put_in_team(client_t *c, game_t *game, size_t i)
// {
//     logs(INFO, "Client %d is trying to be an AI\n", c->fd);
//     c->type = AI;
//     // c->entrypoint = &ai_entrypoint;
//     if (init_ai(game, c, &game->teams->data[i])) {
//         send_client(c, "ko\n");
//         logs(INFO, "No more eggs to place %d\n", c->fd);
//         return ERROR;
//     }
//     logs(INFO, "AI inited\n");
//     return SUCCESS;
// }

// static void send_eggs(client_t *c, team_t *team)
// {
//     for (__auto_type i = 0ul; i < team->eggs->size; i++)
//         send_client(
//             c,
//             "smg eni %d %d %d\n",
//             team->eggs->data[i]->id,
//             team->eggs->data[i]->pos.x,
//             team->eggs->data[i]->pos.y
//         );
// }

// static void send_ais(client_t *c, ai_t *ai)
// {
//     send_client(
//         c,
//         "pnw %d %d %d %d %d %s\n",
//         ai->id,
//         ai->pos.x,
//         ai->pos.y,
//         ai->dir + 1,
//         ai->level,
//         ai->team->name
//     );
// }

// static int init_gui(client_t *c, game_t *game, client_t *clients)
// {
//     // map_size("", c, game, clients);
//     // request_time("", c, game, clients);
//     // map_content_full("", c, game, clients);
//     // team_names("", c, game, clients);
//     for (__auto_type i = 0ul; i < game->teams->size; i++)
//         send_eggs(c, &game->teams->data[i]);
//     for (__auto_type i = 0ul; i < game->ais->size; i++)
//         send_ais(c, &game->ais->data[i]);
//     return 0;
// }

void unset_command(client_t *c, command_state_t *s)
{
    if (strcmp(s->args->data[0]->data, "GRAPHIC") == 0) {
        c->type = GUI;
        return logs(INFO, "Client %d is a GUI\n", c->fd);
    }
    if (s->game->teams == NULL) {
        return logs(WARNING, "No teams set\n");
    }
    for (size_t i = 0; i < s->game->teams->size; i++)
        if (strcmp(s->args->data[0]->data, s->game->teams->data[i].name) == 0) {
            c->type = AI;
            return logs(
                INFO,
                "Client %d is a AI of team %s\n",
                c->fd,
                s->game->teams->data[i].name
            );
        }
    send_invalid_args(c);
}
