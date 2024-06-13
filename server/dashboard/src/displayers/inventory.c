/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** inventory
*/

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "core/types/ai.h"
#include "core/types/object.h"

#include "dashboard/internal.h"

static int display_object(const char *const name, size_t count, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "%s %ld", name, count);
    DrawText(txt, x, y, FONT_SIZE, WHITE);
    free(txt);
    return FONT_SIZE;
}

int display_inventory(client_t *client, int x, int y)
{
    int pixel_drawn = 0;

    for (size_t i = 0; i < OBJ_COUNT; i++) {
        pixel_drawn +=
            display_object(all_obj[i].name, client->ai->inventory[i], x, y);
        y += FONT_SIZE;
    }
    return pixel_drawn;
}
