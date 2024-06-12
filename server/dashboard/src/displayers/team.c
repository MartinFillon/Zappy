/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "core/types/ai.h"

#include "dashboard/internal.h"

int display_team(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "Team: %s", ai->team->name);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
