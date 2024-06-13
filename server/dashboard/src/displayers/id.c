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

int display_id(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "AI %d", client->ai->id);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
