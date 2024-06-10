/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_program
*/

#include "core/client.h"
#include "logger.h"
#include "macros.h"
#include "core/router/router.h"
#include "args_info.h"

int init_program(args_infos_t *args, zappy_t *z)
{
    logs(INFO, "Starting server on port %d\n", args->port);
    z->server.fd = server_init(args->port);
    if (z->server.fd == ERROR)
        return ERROR;
    z->server.router = init_router();
    if (z->server.router == NULL)
        return ERROR;
    logs(INFO, "Server up and running on port %d\n", args->port);
    logs(INFO, "Initailizing game\n");
    z->game = init_game(args);
    z->clients = vec_create_client_list(10);
    logs(INFO, "Game successfully initialised\n");
    return SUCCESS;
}
