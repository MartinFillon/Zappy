/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loop
*/

#include "logger.h"
#include "macros.h"
#include "server.h"
#include "zappy.h"
#include "args_info.h"

int loop_server(args_infos_t *args)
{
    zappy_t z = {0};
    int retval = 0;

    if (init_program(args, &z))
        return ERROR;
    while (!retval && !check_end(z.clients)) {
        fill_fd_set(&z);
        retval = select_server(&z);
        kill_dead_ais(z.clients, z.game.ais);
        exec_clients(&z);
        check_eating(z.clients);
        refill_map(&z.game);
    }
    destroy_program(&z);
    logs(INFO, "Server shutting down\n");
    return SUCCESS;
}
