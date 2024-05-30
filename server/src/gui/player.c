/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_position
*/

#include <stdlib.h>
#include "client.h"
#include "types/client.h"

bool parse_number(char *args, long *n)
{
    char *end;

    *n = strtol(args, &end, 10);
    if (end[0] != '\0' || *n < 0)
        return false;
    return true;
}

static void send_infos(client_t *c, ai_t *ai, size_t nb)
{
    send_client(
        c,
        "ppo %lu %lu %lu %d %d %s\n",
        nb,
        ai->pos.x,
        ai->pos.y,
        ai->dir,
        ai->level,
        ai->team
    );
}

void player_position(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    long nb = -1;

    (void) clients;
    if (c->type != GUI)
        return;
    if (parse_number(args, &nb) == false || (size_t)nb > g->ais->size)
        return send_client(c, "sbp\n");
    return send_infos(c, &g->ais->data[nb], nb);
}

void player_level(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    long nb = -1;

    (void) clients;
    if (c->type != GUI)
        return;
    if (parse_number(args, &nb) == false || (size_t)nb > g->ais->size)
        return send_client(c, "sbp\n");
    return send_client(c, "plv %ld %d", nb, g->ais->data[nb].level);
}

static void send_inventory(client_t *c, ai_t *ai, size_t nb)
{
    send_client(
        c,
        "pin %lu %ld %ld %lu %lu %lu %lu %lu %lu %lu\n",
        nb,
        ai->pos.x,
        ai->pos.y,
        ai->inventory.food,
        ai->inventory.linemate,
        ai->inventory.deraumere,
        ai->inventory.sibur,
        ai->inventory.mendiane,
        ai->inventory.phiras,
        ai->inventory.thystame
    );
}

void player_inventory(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    long nb = -1;

    (void) clients;
    if (c->type != GUI)
        return;
    if (parse_number(args, &nb) == false || (size_t)nb > g->ais->size)
        return send_client(c, "sbp\n");
    return send_inventory(c, &g->ais->data[nb], nb);
}
