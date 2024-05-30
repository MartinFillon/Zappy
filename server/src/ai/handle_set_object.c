/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_set_object
*/

#include "types/ai.h"
#include "types/object.h"
#include "utils.h"
#include "client.h"
#include "map.h"

static bool try_decrement_item(size_t *item_quantity)
{
    if (*item_quantity) {
        (*item_quantity)--;
        return true;
    }
    return false;
}

static bool check_item(ai_t *ai, enum object_e obj)
{
    switch (obj) {
        case FOOD:
            return try_decrement_item(&ai->inventory.food);
        case LINEMATE:
            return try_decrement_item(&ai->inventory.linemate);
        case DERAUMERE:
            return try_decrement_item(&ai->inventory.deraumere);
        case SIBUR:
            return try_decrement_item(&ai->inventory.sibur);
        case MENDIANE:
            return try_decrement_item(&ai->inventory.mendiane);
        case PHIRAS:
            return try_decrement_item(&ai->inventory.phiras);
        case THYSTAME:
            return try_decrement_item(&ai->inventory.thystame);
    }
    return false;
}

static void set_object_down(
    client_t *cli,
    map_t *map,
    const struct obj_name_s *obj
)
{
    if (!check_item(cli->ai, obj->obj))
        return send_client(cli, "ko\n");
    drop_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj);
    send_client(cli, "ok\n");
}

void handle_set_object(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    map_t *map = game->map;

    if (is_empty(arg))
        return send_client(cli, "ko\n");
    (void) clients;
    for (size_t i = 0; i < NB_OBJ; i++) {
        if (strcmp(arg, all_obj[i].name) == 0) {
            set_object_down(cli, map, &all_obj[i]);
            return;
        }
    }
    send_client(cli, "ko\n");
}
