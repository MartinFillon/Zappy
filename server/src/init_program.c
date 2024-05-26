/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_program
*/

#include "macros.h"
#include "utils.h"
#include "zappy.h"
#include "args_info.h"

int init_program(args_infos_t *args, zappy_t *z)
{
    logger_info("Starting server on port %d\n", args->port);
    z->server.fd = server_init(args->port);
    if (z->server.fd == ERROR)
        return ERROR;
    logger_info("Server up and running on port %d\n", args->port);
    logger_info(
        "Initailizing game\nInitailizing map with size %d %d\n",
        args->width,
        args->height
    );
    z->game = init_game(args);
    return SUCCESS;
}
