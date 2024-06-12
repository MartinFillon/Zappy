/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** display_general
*/

#include <raylib.h>
#include <stdio.h>

#include "core/clock.h"
#include "core/types/game.h"

void display_ticks(zclock_t *const clock, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "Tick %llu", current_tick(clock));
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
}

void display_general_infos(game_t *game)
{
    display_ticks(game->global, 700, 500);
}
