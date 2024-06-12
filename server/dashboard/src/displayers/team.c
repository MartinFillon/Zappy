/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "core/types/client.h"

#include "dashboard/internal.h"

int display_team(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "Team: %s", client->ai->team->name);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
