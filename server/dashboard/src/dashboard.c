/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include <raylib.h>

#include "core/core.h"
#include "core/server.h"

#include "json/json.h"

#include "logger.h"
#include "zappy.h"

#include "dashboard/internal.h"

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

    poll_events(s);
    BeginDrawing();
    ClearBackground(BLACK);
    if (z->game.ais->size == 0)
        wait_for_connections();
    else
        display_clients(z->clients, s);
    display_general_infos(&z->game);
    EndDrawing();
    return core(z) && !WindowShouldClose();
}

static void defaults(struct draw_state_s *st)
{
    st->height = HEIGHT;
    st->width = WIDTH;
    st->fps = FPS;
    st->page = 0;
    st->paging = PAGING;
}

static void deserialize(struct draw_state_s *st, json_data_t *json)
{
    st->fps = json_get_number_raw(json, "fps");
    st->width = json_get_number_raw(json, "width");
    st->height = json_get_number_raw(json, "height");
    st->paging = json_get_number_raw(json, "paging");
    if (st->fps == 0) {
        logs(ERROR_LEVEL, "Bad number for fps using default: %d\n", FPS);
        st->fps = FPS;
    }
    if (st->width == 0) {
        logs(ERROR_LEVEL, "Bad number for width using default: %d\n", WIDTH);
        st->width = WIDTH;
    }
    if (st->height == 0) {
        logs(ERROR_LEVEL, "Bad number for height using default: %d\n", HEIGHT);
        st->height = HEIGHT;
    }
    if (st->paging == 0) {
        logs(ERROR_LEVEL, "Bad number for paging using default: %d\n", PAGING);
        st->paging = PAGING;
    }
}

extern void *init(void)
{
    struct draw_state_s *st = calloc(1, sizeof(struct draw_state_s));
    json_data_t *f = json_from_file("dashboard_config.json");

    if (!f) {
        logs(
            ERROR_LEVEL,
            "Bad json in config, or config not found, using defaults\n"
        );
        defaults(st);
    } else {
        deserialize(st, f);
    }
    init_raylib(st);
    json_free(f);
    return st;
}

extern void destroy_renderer(void *state)
{
    struct draw_state_s *st = state;

    free(st);
    return;
}
