/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** core
*/

#include "zappy.h"

int core(zappy_t *z)
{
    int retval = 0;

    fill_fd_set(z);
    retval = select_server(z);
    kill_dead_ais(z->clients, z->game.ais);
    exec_clients(z);
    check_eating(z->clients);
    refill_map(&z->game);
    return !retval && !check_end(z->clients);
}
