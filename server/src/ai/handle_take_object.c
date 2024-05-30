/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_take_object
*/

#include "utils.h"
#include "client.h"
#include "map.h"

static void increment_item(client_t *cli, size_t *item_quantity)
{
    (*item_quantity)++;
    send_client(cli, "ok\n");
}

static void take_object_down(
    client_t *cli,
    map_t *map,
    const struct obj_name_s *obj
)
{
    if (!take_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj))
        return send_client(cli, "ko\n");
    switch (obj->obj) {
        case FOOD:
            return increment_item(cli, &cli->ai->inventory.food);
        case LINEMATE:
            return increment_item(cli, &cli->ai->inventory.linemate);
        case DERAUMERE:
            return increment_item(cli, &cli->ai->inventory.deraumere);
        case SIBUR:
            return increment_item(cli, &cli->ai->inventory.sibur);
        case MENDIANE:
            return increment_item(cli, &cli->ai->inventory.mendiane);
        case PHIRAS:
            return increment_item(cli, &cli->ai->inventory.phiras);
        case THYSTAME:
            return increment_item(cli, &cli->ai->inventory.thystame);
    }
}

void handle_take_object(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    map_t *map = game->map;

    (void) clients;
    if (is_empty(arg))
        return send_client(cli, "ko\n");
    for (size_t i = 0; i < NB_OBJ; i++) {
        if (strcmp(arg, all_obj[i].name) == 0) {
            take_object_down(cli, map, all_obj + i);
            return;
        }
    }
    send_client(cli, "ko\n");
}
