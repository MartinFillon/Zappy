/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_incantation
*/

#include <stdlib.h>
#include "client.h"
#include "incantation.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/game.h"
#include "types/map.h"
#include "types/object.h"
#include "types/position.h"
#include "utils.h"

static void freeze_ais(game_t *game, pos_t *pos, int id)
{
    struct vector_ai_t *ais = game->ais;

    for (size_t i = 0; i < ais->size; i++) {
        if (is_coord_equal(pos, &ais->data[i].pos)) {
            ais->data[i].incant.is_incant = true;
            ais->data[i].incant.id_incant = id;
        }
    }
}

static void unfreeze_ais(game_t *game, int id)
{
    struct vector_ai_t *ais = game->ais;

    for (size_t i = 0; i < ais->size; i++) {
        if (ais->data[i].incant.is_incant && ais->data[i].id == id) {
            ais->data[i].incant.is_incant = false;
        }
    }
}

static void increment_all_levels(game_t *game, int id)
{
    struct vector_ai_t *ais = game->ais;

    for (size_t i = 0; i < ais->size; i++) {
        if (ais->data[i].id == id) {
            ais->data[i].level++;
        }
    }
}

static void consume_tile_incantation(
    size_t lvl_idx,
    map_t *map,
    size_t y,
    size_t x
)
{
    struct tile_s *tile = &map->arena[y][x];
    const size_t *tile_req = incant_req[lvl_idx].ressource;

    for (size_t i = LINEMATE; i < OBJ_COUNT; i++)
        tile->content[i] -= tile_req[i];
}

static bool verif_level_specification(ai_t *ai, map_t *map)
{
    pos_t *pos = &ai->pos;
    size_t idx = ai->level - 1;
    size_t *con = NULL;
    const size_t *tile = NULL;

    if (incant_req[idx].nb_player != map->arena[pos->y][pos->x].players->size)
        return false;
    con = map->arena[pos->y][pos->x].content;
    tile = incant_req[idx].ressource;
    for (size_t i = LINEMATE; i < OBJ_COUNT; i++)
        if (!(con[i] >= tile[i]))
            return false;
    return true;
}

void handle_end_incantation(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    bool first = cli->ai->incant.last_verif;

    (void)clients;
    if (!is_empty(arg))
        return prepare_response_cat(&cli->io, "ko\n");
    cli->ai->incant.is_incant = false;
    cli->ai->incant.last_verif = verif_level_specification(cli->ai, game->map);
    unfreeze_ais(game, cli->ai->id);
    if (first == false || cli->ai->incant.last_verif == false)
        return prepare_response_cat(&cli->io, "ko\n");
    prepare_response_cat(&cli->io, "Current level: %d\n", cli->ai->level);
    consume_tile_incantation(
        cli->ai->level, game->map, cli->ai->pos.y, cli->ai->pos.x
    );
    increment_all_levels(game, cli->ai->id);
}

void handle_start_incantation(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    (void)clients;
    if (!is_empty(arg))
        return prepare_response_cat(&cli->io, "ko\n");
    freeze_ais(game, &cli->ai->pos, cli->ai->id);
    cli->ai->incant.last_verif = verif_level_specification(cli->ai, game->map);
    if (cli->ai->incant.last_verif)
        prepare_response_cat(&cli->io, "Elevation underway\n");
    else
        prepare_response_cat(&cli->io, "ok\n");
}
