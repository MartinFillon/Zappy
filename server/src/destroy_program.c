/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy_program
*/

#include <unistd.h>
#include "core/client.h"
#include "zappy.h"

void destroy_program(zappy_t *z)
{
    free_wifi(&z->server);
    destroy_game(&z->game);
    for (size_t i = 0; i < z->clients->size; i++)
        destroy_client(z->clients->data[i]);
    vec_destroy_client_list(z->clients);
}
