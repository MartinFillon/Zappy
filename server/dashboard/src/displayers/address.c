/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** address
*/

#include <raylib.h>

#include "core/types/client.h"

#include "dashboard/internal.h"

int display_address(client_t *client, int x, int y)
{
    DrawText(client->address, x, y, FONT_SIZE, WHITE);
    return FONT_SIZE;
}
