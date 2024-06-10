/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include "core.h"
#include "logger.h"
#include "server.h"
#include "zappy.h"

extern bool server_runner(zappy_t *z)
{
    static bool fst = true;

    if (fst)
        logs(INFO, "Starting as base without dashboard\n");
    fst = 0;
    return core(z);
}
