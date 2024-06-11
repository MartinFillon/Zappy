/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include "core/core.h"
#include "core/server.h"
#include "logger.h"
#include "zappy.h"

extern bool server_runner(zappy_t *z, void *dt)
{
    static bool fst = true;

    (void)dt;
    if (fst)
        logs(INFO, "Starting as base without dashboard\n");
    fst = 0;
    return core(z);
}

extern void *init(void)
{
    return NULL;
}

extern void destroy_renderer(void *state)
{
    (void)state;
    return;
}
