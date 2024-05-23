/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_position
*/

#include <stdlib.h>
#include "client.h"
#include "types/client.h"

static bool parse_number(char *args, long *n)
{
    char *end;

    *n = strtol(args, &end, 10);
    if (end[0] != '\0' || n < 0)
        return false;
    return true;
}

static void send_infos(client_t *c, ai_t *ai, size_t nb)
{
    send_client(
        c,
        "ppo %lu %lu %lu %d %d %s\n",
        nb,
        ai->x,
        ai->y,
        ai->dir,
        ai->level,
        ai->team
    );
}

void player_position(char *args, client_t *c, game_t *g)
{
    long nb = -1;

    if (c->type != GUI)
        return;
    if (parse_number(args, &nb) == false || (size_t)nb > g->ai_count)
        return send_client(c, "sbp\n");
    return send_infos(c, &g->ais[nb], nb);
}
