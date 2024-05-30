/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_program
*/

#include "macros.h"
#include "logger.h"
#include "zappy.h"
#include "args_info.h"

int init_program(args_infos_t *args, zappy_t *z)
{
    logs(INFO, "Starting server on port %d\n", args->port);
    z->server.fd = server_init(args->port);
    if (z->server.fd == ERROR)
        return ERROR;
    logs(INFO, "Server up and running on port %d\n", args->port);
    logs(INFO, "Initailizing game\n");
    z->game = init_game(args);
    logs(INFO, "Game successfully initialised\n");
    return SUCCESS;
}
