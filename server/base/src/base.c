/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include "logger.h"
#include "server.h"
#include "zappy.h"
#include "core.h"

extern bool server_runner(zappy_t *z)
{
    logs(INFO, "Starting as base without dashboard\n");
    return core(z);
}
