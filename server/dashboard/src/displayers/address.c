/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** address
*/

#include <raylib.h>
#include <stdio.h>

#include "core/types/client.h"

#include "dashboard/internal.h"

int display_address(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "%s:%u", client->address, client->port);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}
