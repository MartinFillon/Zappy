/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_set_object
*/

#include "client.h"
#include "map.h"
#include "router/route.h"
#include "types/ai.h"
#include "types/object.h"
#include "utils.h"

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
        return prepare_response(&cli->io, "ko\n");
    drop_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj);
    prepare_response(&cli->io, "ok\n");
}

void handle_set_object(client_t *cli, command_state_t *s)
{
    map_t *map = s->game->map;

    for (size_t i = 0; i < NB_OBJ; i++) {
        if (strcmp(s->args->data[1]->data, all_obj[i].name) == 0) {
            set_object_down(cli, map, &all_obj[i]);
            return;
        }
    }
    prepare_response(&cli->io, "ko\n");
}
