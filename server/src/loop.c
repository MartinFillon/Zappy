/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loop
*/

#include "core.h"
#include "loader.h"
#include "logger.h"
#include "macros.h"
#include "server.h"
#include "zappy.h"
#include "args_info.h"

lib_t open_dhl(char const *file);
void close_dhl(lib_t *l);

int loop_server(args_infos_t *args)
{
    zappy_t z = {0};
    lib_t l = open_dhl("server/base.so");

    if (!l.loop || init_program(args, &z))
        return ERROR;
    while (l.loop(&z))
        ;
    destroy_program(&z);
    close_dhl(&l);
    logs(INFO, "Server shutting down\n");
    return SUCCESS;
}
