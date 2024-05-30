/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_ais_info
*/

#include "logger.h"
#include "zappy.h"

static void display_ai(ai_t *ai)
{
    logs(
        INFO,
        "AI [%d][Team: %s] (%s) pos (%d, %d) | level %d\n",
        ai->id,
        ai->team->name,
        ai->alive ? "alive" : "dead",
        ai->pos.y,
        ai->pos.x,
        ai->level
    );
}

static void display_ai_ressources(ai_t *ai)
{
    inventory_t *inventory = &ai->inventory;

    logs(
        INFO,
        "AI [%d][Team: %s] (%s)\n"
        "Ressources: %d %d %d %d %d %d %d\n",
        ai->id,
        ai->team->name,
        ai->alive ? "alive" : "dead",
        inventory->food,
        inventory->linemate,
        inventory->deraumere,
        inventory->sibur,
        inventory->mendiane,
        inventory->phiras,
        inventory->thystame
    );
}

void handle_display_ais(zappy_t *z)
{
    struct vector_ai_t *ais = z->game.ais;

    for (size_t i = 0; i < ais->size; i++) {
        display_ai(&ais->data[i]);
    }
}

void handle_ressources_ais(zappy_t *z)
{
    struct vector_ai_t *ais = z->game.ais;

    for (size_t i = 0; i < ais->size; i++) {
        display_ai_ressources(&ais->data[i]);
    }
}
