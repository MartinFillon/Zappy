/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** id
*/

#include <raylib.h>
#include <stdio.h>

#include "core/types/ai.h"

int display_id(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "AI %d", ai->id);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
    return 20;
}
