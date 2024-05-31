/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy_program
*/

#include <unistd.h>
#include "zappy.h"

void destroy_program(zappy_t *z)
{
    free_wifi(&z->server);
    destroy_game(&z->game);
    for (__auto_type i = 0; i < SOMAXCONN; i++) {
        if (z->clients[i].fd > 0) {
            close(z->clients[i].fd);
        }
    }
}
