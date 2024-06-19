/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation_end
*/

#include <stdio.h>
#include <unistd.h>
#include "core/client.h"
#include "core/map.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/incantation.h"
#include "core/types/object.h"
#include "core/types/position.h"
#include "logger.h"
#include "macros.h"
#include "utils.h"

static void increment_all_levels(
    game_t *game,
    int id_incant,
    struct client_list *cls
)
{
    struct vector_ai_t *ais = game->ais;

    for (size_t i = 0; i < ais->size; i++) {
        if (ais->data[i]->incant.is_incant &&
            ais->data[i]->incant.id_incant == id_incant) {
            ais->data[i]->level++;
            broadcast_to(
                GUI, cls, "plv %d %ld\n", ais->data[i]->id, ais->data[i]->level
            );
        }
    }
}

static void consume_tile_incantation(
    size_t lvl_idx,
    map_t *map,
    pos_t *pos,
    struct client_list *cls
)
{
    struct tile_s *tile = &map->arena[pos->y][pos->x];
    const size_t *tile_req = incant_req[lvl_idx].ressource;

    broadcast_to(GUI, cls, "bct %d %d", pos->x, pos->y);
    for (size_t i = LINEMATE; i < OBJ_COUNT; i++) {
        tile->content[i] -= tile_req[i];
        broadcast_to(GUI, cls, " %ld", tile->content[i]);
    }
    broadcast_to(GUI, cls, "\n");
}

static size_t count_nb_ai_incant(game_t *g, struct tile_s *tile, ai_t *ai)
{
    struct vector_ai_t *ais = g->ais;
    ai_t *oth = NULL;
    size_t count = 0;

    for (size_t i = 0; i < ais->size; i++) {
        oth = ais->data[i];
        for (size_t k = 0; k < tile->players->size; k++) {
            count += oth->id == tile->players->data[k] &&
                oth->incant.is_incant &&
                oth->incant.id_incant == ai->incant.id_incant;
        }
    }
    return count;
}

static bool verif_end_specification(ai_t *ai, game_t *game)
{
    pos_t *pos = &ai->pos;
    size_t idx = ai->level - 1;
    size_t nb_player =
        count_nb_ai_incant(game, &game->map->arena[pos->y][pos->x], ai);

    if (nb_player < incant_req[idx].nb_player) {
        logs(DEBUG, "Not enough player for end_incantation.\n");
        return false;
    }
    if (!verif_tile_requirement(
            game->map->arena[pos->y][pos->x].content, incant_req[idx].ressource
        )) {
        logs(DEBUG, "Tiles requirements are not fullfilled in end.\n");
        return false;
    }
    return true;
}

static void end_ais_elevation(
    struct client_list *clis,
    client_t *cli,
    char *msg
)
{
    client_t *oth = NULL;

    for (size_t i = 0; i < clis->size; i++) {
        oth = clis->data[i];
        if (oth->type == GUI)
            continue;
        if (cli->ai->id != oth->ai->id &&
            is_coord_equal(&cli->ai->pos, &oth->ai->pos) &&
            oth->ai->incant.is_incant &&
            oth->ai->incant.id_incant == cli->ai->incant.id_incant) {
            unfreeze_ai(oth->ai);
            prepare_response_cat(&oth->io, msg);
        }
    }
    unfreeze_ai(cli->ai);
    prepare_response_cat(&cli->io, msg);
}

static void send_incantation_end(
    client_t *cli,
    struct client_list *clients,
    int result
)
{
    broadcast_to(
        GUI, clients, "pie %d %d %d\n", cli->ai->pos.x, cli->ai->pos.y, result
    );
}

void handle_end_incantation(client_t *cli, command_state_t *s)
{
    bool first = cli->ai->incant.last_verif;
    char msg[BUFF_SIZE] = {0};

    cli->ai->incant.last_verif = verif_end_specification(cli->ai, s->game);
    if (first == false) {
        unfreeze_ai(cli->ai);
        logs(DEBUG, "Start incantation failed, so end too.\n");
        send_incantation_end(cli, s->clients, 0);
        return prepare_response_cat(&cli->io, "ko\n");
    }
    if (cli->ai->incant.last_verif) {
        consume_tile_incantation(
            cli->ai->level - 1, s->game->map, &cli->ai->pos, s->clients
        );
        increment_all_levels(s->game, cli->ai->id, s->clients);
        sprintf(msg, "Current level: %ld\n", cli->ai->level);
    } else {
        sprintf(msg, "ko\n");
    }
    end_ais_elevation(s->clients, cli, msg);
    send_incantation_end(cli, s->clients, 1);
}
