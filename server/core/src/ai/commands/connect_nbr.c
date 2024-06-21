/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_connect_nbr
*/

#include "core/client.h"
#include "core/router/route.h"
#include "core/types/client.h"
#include "logger.h"

void handle_connect_nbr(client_t *cli, command_state_t *s)
{
    (void)s;
    prepare_response_cat(&cli->io, "%d\n", cli->ai->team->eggs->size);
    logs(
        INFO,
        "Team %s has %ld eggs\n",
        cli->ai->team->name,
        cli->ai->team->eggs->size
    );
}
