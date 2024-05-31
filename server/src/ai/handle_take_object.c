/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_take_object
*/

#include "client.h"
#include "map.h"
#include "router/route.h"

static void increment_item(client_t *cli, size_t *item_quantity)
{
    (*item_quantity)++;
    prepare_response(&cli->io, "ok\n");
}

static void take_object_down(
    client_t *cli,
    map_t *map,
    const struct obj_name_s *obj
)
{
    if (!take_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj))
        return prepare_response(&cli->io, "ko\n");
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

void handle_take_object(client_t *cli, command_state_t *s)
{
    map_t *map = s->game->map;

    for (size_t i = 0; i < NB_OBJ; i++) {
        if (strcmp(s->args->data[1]->data, all_obj[i].name) == 0) {
            take_object_down(cli, map, all_obj + i);
            return;
        }
    }
    prepare_response(&cli->io, "ko\n");
}
