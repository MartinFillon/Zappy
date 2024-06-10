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

static void display_object(const char *const name, size_t count, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "%s %ld", name, count);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
}

void display_inventory(ai_t *ai, int x, int y)
{
    for (size_t i = 0; i < OBJ_COUNT; i++) {
        display_object(all_obj[i].name, ai->inventory[i], x, y);
        y += 20;
    }
}
