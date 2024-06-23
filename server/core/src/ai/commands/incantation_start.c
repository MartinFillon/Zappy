/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_incantation
*/

#include <stdio.h>
#include <stdlib.h>
#include "core/client.h"
#include "core/map.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/incantation.h"
#include "core/types/map.h"
#include "core/types/position.h"
#include "logger.h"
#include "utils.h"

static size_t count_nb_ai_available(
    game_t *g,
    struct tile_s *tile,
    size_t level
)
{
    struct vector_ai_t *ais = g->ais;
    ai_t *ai = NULL;
    size_t count = 0;

    for (size_t i = 0; i < ais->size; i++) {
        ai = ais->data[i];
        for (size_t k = 0; k < tile->players->size; k++) {
            count += ai->id == tile->players->data[k] &&
                !ai->incant.is_incant && 
                ai->level == level;
        }
    }
    return count;
}

static bool verif_start_specification(ai_t *ai, game_t *game)
{
    pos_t *pos = &ai->pos;
    size_t idx = ai->level - 1;
    size_t nb_player = count_nb_ai_available(
        game, &game->map->arena[pos->y][pos->x], ai->level);

    if (nb_player < incant_req[idx].nb_player) {
        logs(DEBUG, "Not enough player for start_incantation.\n");
        return false;
    }
    if (!verif_tile_requirement(
            game->map->arena[pos->y][pos->x].content, incant_req[idx].ressource
        )) {
        logs(DEBUG, "Tiles requirements are not fullfilled in start.\n");
        return false;
    }
    return true;
}

static void start_ais_elevation(struct client_list *clis, client_t *cli)
{
    client_t *oth = NULL;
    size_t idx = cli->ai->level - 1;
    size_t n = 0;

    for (size_t i = 0; n < incant_req[idx].nb_player && i < clis->size; i++) {
        oth = clis->data[i];
        if (oth->type != AI)
            continue;
        if (is_coord_equal(&cli->ai->pos, &oth->ai->pos) &&
            !oth->ai->incant.is_incant && oth->ai->level == cli->ai->level) {
            n++;
            freeze_ai(oth->ai, cli->ai->id);
            prepare_response_cat(&oth->io, "Elevation underway\n");
        }
    }
}

static void send_incantation_start(client_t *cli, struct client_list *clients)
{
    broadcast_to(
        GUI,
        clients,
        "pic %d %d %d %d",
        cli->ai->pos.x,
        cli->ai->pos.y,
        cli->ai->level,
        cli->ai->id
    );
    for (size_t i = 0; i < clients->size; i++)
        if (clients->data[i]->type == AI &&
            clients->data[i]->ai->incant.is_incant &&
            clients->data[i]->ai->id != clients->data[i]->ai->incant.id_incant)
            broadcast_to(GUI, clients, " %d", clients->data[i]->ai->id);
    broadcast_to(GUI, clients, "\n");
}

void handle_start_incantation(client_t *cli, command_state_t *s)
{
    str_t *end_incant = NULL;

    cli->ai->incant.last_verif = verif_start_specification(cli->ai, s->game);
    if (cli->ai->incant.last_verif) {
        start_ais_elevation(s->clients, cli);
    } else {
        freeze_ai(cli->ai, cli->ai->id);
        prepare_response_cat(&cli->io, "ko\n");
    }
    end_incant = str_snew("End_Incantation");
    if (!end_incant) {
        logs(ERROR_LEVEL, "Allocation error\n");
        return;
    }
    send_incantation_start(cli, s->clients);
    queue_pushfront_queue_command_t(cli->commands, end_incant);
}
