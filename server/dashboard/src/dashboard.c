/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include <raylib.h>

#include "core/core.h"
#include "core/server.h"
#include "dashboard/internal.h"
#include "logger.h"
#include "zappy.h"

static void init_raylib(struct draw_state_s *st)
{
    logs(INFO, "Starting window with size: %d %d\n", st->width, st->height);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(st->width, st->height, "Zappy dashboard");
    SetTargetFPS(st->fps);
}

extern bool server_runner(zappy_t *z, void *dt)
{
    struct draw_state_s *s = dt;

    (void)s;
    BeginDrawing();
    ClearBackground(BLACK);
    if (z->game.ais->size == 0)
        wait_for_connections();
    else
        display_clients(z->clients, s->page, s->page + 4);
    EndDrawing();
    return core(z) && !WindowShouldClose();
}

extern void *init(void)
{
    struct draw_state_s *st = calloc(1, sizeof(struct draw_state_s));

    st->height = 600;
    st->width = 800;
    st->fps = 60;
    st->page = 0;
    init_raylib(st);
    return st;
}
