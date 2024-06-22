/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_set_object
*/

#include "core/client.h"
#include "core/map.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/object.h"
#include "str.h"

static bool try_decrement_item(size_t *item_quantity)
{
    if (*item_quantity) {
        (*item_quantity)--;
        return true;
    }
    return false;
}

static void set_object_down(
    client_t *cli,
    map_t *map,
    const struct obj_name_s *obj
)
{
    if (!try_decrement_item(&cli->ai->inventory[obj->obj]))
        return prepare_response_cat(&cli->io, "ko\n");
    drop_item(map, cli->ai->pos.x, cli->ai->pos.y, obj->obj);
    prepare_response_cat(&cli->io, "ok\n");
}

void handle_set_object(client_t *cli, command_state_t *s)
{
    map_t *map = s->game->map;
    size_t i = 0;

    for (; i < NB_OBJ; i++) {
        if (strcmp(s->args->data[1]->data, all_obj[i].name) == 0) {
            set_object_down(cli, map, &all_obj[i]);
            broadcast_to(GUI, s->clients, "pdr %d %d\n", cli->ai->id, i);
            return;
        }
    }
    prepare_response_cat(&cli->io, "ko\n");
}
