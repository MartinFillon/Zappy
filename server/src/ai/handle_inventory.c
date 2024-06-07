/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_inventory
*/

#include <stdlib.h>
#include "client.h"
#include "router/route.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/object.h"

void handle_inventory(client_t *cli, command_state_t *s)
{
    size_t *inv = cli->ai->inventory;

    (void)s;
    prepare_response(
        &cli->io,
        "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]\n",
        "food",
        inv[FOOD],
        "linemate",
        inv[LINEMATE],
        "deraumere",
        inv[DERAUMERE],
        "sibur",
        inv[SIBUR],
        "mendiane",
        inv[MENDIANE],
        "phiras",
        inv[PHIRAS],
        "thystame",
        inv[THYSTAME]
    );
}
