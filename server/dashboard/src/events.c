/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** events
*/

#include <raylib.h>

#include "dashboard/events.h"
#include "dashboard/internal.h"

void poll_events(struct draw_state_s *st)
{
    for (size_t i = 0; KEY_EVENTS[i].f != NULL; i++) {
        if (IsKeyPressed(KEY_EVENTS[i].key))
            KEY_EVENTS[i].f(st);
    }
}
