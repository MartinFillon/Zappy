/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loop
*/

#include "core.h"
#include "logger.h"
#include "macros.h"
#include "server.h"
#include "zappy.h"
#include "args_info.h"

int loop_server(args_infos_t *args)
{
    zappy_t z = {0};

    if (init_program(args, &z))
        return ERROR;
    while (core(&z))
        ;
    destroy_program(&z);
    logs(INFO, "Server shutting down\n");
    return SUCCESS;
}
