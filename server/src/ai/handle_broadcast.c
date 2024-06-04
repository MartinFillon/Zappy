/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_broadcast
*/

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "client.h"
#include "router/route.h"
#include "str.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/game.h"
#include "types/map.h"
#include "types/position.h"
#include "utils.h"

static bool valid_client(client_t *to_check, client_t *banned)
{
    return to_check->fd != 0 && to_check->ai->id != banned->ai->id;
}

static void get_starting_pos(
    pos_t *start_dest,
    pos_t *orig_pos,
    enum direction dir,
    map_t *map
)
{
    start_dest->x = orig_pos->x;
    start_dest->y = orig_pos->y;
    switch (dir) {
        case UP:
            start_dest->y = modulo(start_dest->y - 1, map->y);
            break;
        case RIGHT:
            start_dest->x = start_dest->x + 1;
            break;
        case DOWN:
            start_dest->y = start_dest->y + 1;
            break;
        case LEFT:
            start_dest->x = modulo(start_dest->x - 1, map->x);
            break;
        default:
            break;
    }
}

static bool get_min_distance(pos_t *src_pos, pos_t *tile_pos, double *old_dist)
{
    pos_t vec_dist = {0};
    double new_dist = 0.f;

    vec_dist.x = tile_pos->x - src_pos->x;
    vec_dist.y = tile_pos->y - src_pos->y;
    new_dist = sqrt(vec_dist.x * vec_dist.x + vec_dist.y * vec_dist.y);
    if (new_dist < *old_dist) {
        *old_dist = new_dist;
        return true;
    }
    return false;
}

static int get_shortest_distance_sound(
    pos_t *src_pos,
    pos_t *pos,
    enum direction dir,
    map_t *map
)
{
    double dist = DBL_MAX;
    size_t nb_move = 1;
    size_t i = 1;
    size_t sound_idx = 0;

    dir = modulo((dir - 1), NB_DIR);
    for (; i <= 8; i++) {
        if (nb_move == 0) {
            dir = modulo((dir - 1), NB_DIR);
            nb_move = 2;
        }
        if (get_min_distance(src_pos, pos, &dist))
            sound_idx = i;
        move_by_dir(pos, dir, map);
        nb_move--;
    }
    return sound_idx;
}

static void send_to_everyone(
    char const *msg,
    client_t *clis,
    client_t *c,
    game_t *g
)
{
    enum direction dir = UP;
    pos_t pos = {0};

    for (int i = 0; i < SOMAXCONN; i++) {
        if (clis[i].type == AI && valid_client(&clis[i], c)) {
            dir = clis[i].ai->dir;
            get_starting_pos(&pos, &clis[i].ai->pos, dir, g->map);
            prepare_response_cat(
                &clis[i].io,
                "message %d, %s\n",
                get_shortest_distance_sound(&c->ai->pos, &pos, dir, g->map),
                msg
            );
        }
    }
}

void handle_broadcast(client_t *cli, command_state_t *s)
{
    char *msg = str_cstr(s->args->data[1]);

    prepare_response_cat(&cli->io, "ok\n");
    send_to_everyone(msg, s->clients, cli, s->game);
    broadcast_to(GUI, s->clients, "pbc %d %s\n", cli->ai->id, msg);
    free(msg);
}
