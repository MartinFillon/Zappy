/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** dashboard
*/

#include "core/server.h"
#include "logger.h"
#include "zappy.h"

extern bool server_runner(zappy_t *z)
{
    (void)z;
    logs(INFO, "Starting dashboard\n");
    return true;
}
