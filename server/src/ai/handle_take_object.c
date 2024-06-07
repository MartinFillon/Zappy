/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_take_object
*/

#include "client.h"
#include "map.h"
#include "router/route.h"
#include "str.h"

static void increment_item(client_t *cli, size_t *item_quantity)
{
    (*item_quantity)++;
    prepare_response_cat(&cli->io, "ok\n");
}

static void take_object_down(
    client_t *cli,
    map_t *map,
    const struct obj_name_s *obj
)
{
    if (!take_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj))
        return prepare_response_cat(&cli->io, "ko\n");
    return increment_item(cli, &cli->ai->inventory[obj->obj]);
}

void handle_take_object(client_t *cli, command_state_t *s)
{
    map_t *map = s->game->map;
    size_t i = 0;

    for (; i < NB_OBJ; i++) {
        if (strcmp(s->args->data[1]->data, all_obj[i].name) == 0) {
            take_object_down(cli, map, all_obj + i);
            return;
        }
    }
    prepare_response_cat(&cli->io, "ko\n");
    broadcast_to(GUI, s->clients, "pgt %d %d\n", cli->ai->id, i);
}
