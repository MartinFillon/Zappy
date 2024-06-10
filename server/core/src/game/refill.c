/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** refill
*/

#include "clock.h"
#include "macros.h"
#include "map.h"
#include "types/game.h"

void refill_map(game_t *game)
{
    if (!has_n_ticks_passed(game->clock, REFILL_TICKS))
        return;
    fill_map(game->map);
    reset_clock(game->clock);
}
