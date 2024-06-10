/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_position
*/

#include <stdlib.h>
#include "core/client.h"
#include "core/middlewares.h"
#include "core/router/route.h"
#include "core/types/client.h"
#include "core/types/object.h"
#include "str.h"

static void send_infos(client_t *c, ai_t *ai, size_t nb)
{
    prepare_response_cat(
        &c->io,
        "ppo %lu %lu %lu %d %d %s\n",
        nb,
        ai->pos.x,
        ai->pos.y,
        ai->dir,
        ai->level,
        ai->team
    );
}

void player_position(client_t *c, command_state_t *com)
{
    long nb = -1;

    if (str_toint(&nb, com->args->data[1]))
        return send_invalid_args(c);
    if ((size_t)nb >= com->game->ais->size)
        return send_invalid_args(c);
    return send_infos(c, &com->game->ais->data[nb], nb);
}

void player_level(client_t *c, command_state_t *com)
{
    long nb = -1;

    if (str_toint(&nb, com->args->data[1]))
        return send_invalid_args(c);
    if ((size_t)nb >= com->game->ais->size)
        return send_invalid_args(c);
    return prepare_response_cat(
        &c->io, "plv %ld %d", nb, com->game->ais->data[nb].level
    );
}

static void send_inventory(client_t *c, ai_t *ai, size_t nb)
{
    prepare_response_cat(&c->io, "pin %lu %ld %ld", nb, ai->pos.x, ai->pos.y);
    for (size_t i = FOOD; i < OBJ_COUNT; i++)
        prepare_response_cat(&c->io, " %lu", ai->inventory[i]);
    prepare_response_cat(&c->io, "\n");
}

void player_inventory(client_t *c, command_state_t *com)
{
    long nb = -1;

    if (str_toint(&nb, com->args->data[1]))
        return send_invalid_args(c);
    if ((size_t)nb >= com->game->ais->size)
        return send_invalid_args(c);
    return send_inventory(c, &com->game->ais->data[nb], nb);
}
