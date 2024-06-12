/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** level
*/

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "core/types/ai.h"

#include "dashboard/internal.h"

int display_level(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "level %ld", ai->level);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
