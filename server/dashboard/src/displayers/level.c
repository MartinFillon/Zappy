/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** level
*/

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "core/types/client.h"

#include "dashboard/internal.h"

int display_level(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "level %ld", client->ai->level);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
