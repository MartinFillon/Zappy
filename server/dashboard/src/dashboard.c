/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include <raylib.h>

#include "core/core.h"
#include "core/server.h"
#include "logger.h"
#include "zappy.h"

struct draw_state_s {
    size_t width;
    size_t height;
    size_t fps;
};

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
    DrawText("Waiting for connections...", 190, 200, 20, WHITE);
    EndDrawing();
    return core(z) && !WindowShouldClose();
}

extern void *init(void)
{
    struct draw_state_s *st = calloc(1, sizeof(struct draw_state_s));

    st->height = 450;
    st->width = 800;
    st->fps = 60;
    init_raylib(st);
    return st;
}
