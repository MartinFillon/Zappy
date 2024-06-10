/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** refill
*/

#include "core/clock.h"
#include "core/map.h"
#include "core/types/game.h"
#include "macros.h"

void refill_map(game_t *game)
{
    if (!has_n_ticks_passed(game->clock, REFILL_TICKS))
        return;
    fill_map(game->map);
    reset_clock(game->clock);
}
