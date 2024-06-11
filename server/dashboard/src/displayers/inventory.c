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

static int display_object(const char *const name, size_t count, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "%s %ld", name, count);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
    return 20;
}

int display_inventory(ai_t *ai, int x, int y)
{
    int pixel_drawn = 0;

    for (size_t i = 0; i < OBJ_COUNT; i++) {
        pixel_drawn += display_object(all_obj[i].name, ai->inventory[i], x, y);
        y += 20;
    }
    return pixel_drawn;
}
