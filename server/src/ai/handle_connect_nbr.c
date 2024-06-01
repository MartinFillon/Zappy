/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_connect_nbr
*/

#include "router/route.h"
#include "types/client.h"
#include "client.h"

void handle_connect_nbr(client_t *cli, command_state_t *s)
{
    (void) s;
    prepare_response(&cli->io, "%d\n", cli->ai->team->eggs->size);
}
