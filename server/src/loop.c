/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loop
*/

#include "core/server.h"
#include "loader.h"
#include "logger.h"
#include "macros.h"
#include "zappy.h"
#include "args_info.h"

int loop_server(args_infos_t *args)
{
    zappy_t z = {0};
    char *file = str_cstr(args->displayer_path);
    lib_t l = open_dhl(file);
    void *dt = NULL;

    free(file);
    if (!l.loop || init_program(args, &z))
        return ERROR;
    dt = l.init(args->level);
    while (l.loop(&z, dt))
        ;
    destroy_program(&z);
    l.destroy(dt);
    close_dhl(&l);
    logs(INFO, "Server shutting down\n");
    return SUCCESS;
}
