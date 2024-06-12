/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** id
*/

#include <raylib.h>
#include <stdio.h>

#include "core/types/ai.h"

#include "dashboard/internal.h"

int display_id(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "AI %d", ai->id);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
