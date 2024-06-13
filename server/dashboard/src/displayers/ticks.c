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

int display_cycle(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(
        &txt,
        "cycle: %llu",
        client->ai->cycles_to_wait != 0 ? current_tick(client->ai->clock) : 0
    );
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    txt = NULL;
    asprintf(&txt, "cycle to wait: %ld", client->ai->cycles_to_wait);
    DrawText(txt, x, y + FONT_SIZE, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE * 2;
}
