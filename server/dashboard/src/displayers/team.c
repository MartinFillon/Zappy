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

int display_team(ai_t *ai, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "Team: %s", ai->team->name);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
    return 20;
}
