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

static void init_raylib(void)
{
    logs(INFO, "Starting window with size: %d %d\n", 800, 450);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 450, "Zappy dashboard");
    SetTargetFPS(60);
}

extern bool server_runner(zappy_t *z)
{
    static bool startup = true;

    if (startup) {
        init_raylib();
        startup = false;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Waiting for connections...", 190, 200, 20, WHITE);
    EndDrawing();
    return core(z) && !WindowShouldClose();
}
