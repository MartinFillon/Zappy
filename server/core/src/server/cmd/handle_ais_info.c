/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_ais_info
*/

#include <stdio.h>
#include "core/types/object.h"
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
    size_t *inventory = ai->inventory;

    logs(
        INFO,
        "AI [%d][Team: %s] (%s)\n"
        "Ressources:",
        ai->id,
        ai->team->name,
        ai->alive ? "alive" : "dead"
    );
    for (size_t i = FOOD; i < OBJ_COUNT; i++)
        dprintf(2, " %lu", inventory[i]);
    dprintf(2, "\n");
}

void handle_display_ais(zappy_t *z, struct vector_str_t *args)
{
    struct vector_ai_t *ais = z->game.ais;

    (void)args;
    for (size_t i = 0; i < ais->size; i++) {
        display_ai(&ais->data[i]);
    }
}

void handle_ressources_ais(zappy_t *z, struct vector_str_t *args)
{
    struct vector_ai_t *ais = z->game.ais;

    (void)args;
    for (size_t i = 0; i < ais->size; i++) {
        display_ai_ressources(&ais->data[i]);
    }
}
