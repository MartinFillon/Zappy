/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ticks
*/

#include <raylib.h>
#include <stdio.h>

#include "core/clock.h"
#include "core/types/ai.h"
#include "dashboard/internal.h"

int display_cycle(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(
        &txt,
        "cycle: %llu",
        ai->cycles_to_wait != 0 ? current_tick(ai->clock) : 0
    );
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    txt = NULL;
    asprintf(&txt, "cycle to wait: %ld", ai->cycles_to_wait);
    DrawText(txt, x, y + FONT_SIZE, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE * 2;
}
