/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_inventory
*/

#include "core/client.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/object.h"

void handle_inventory(client_t *cli, command_state_t *s)
{
    (void)s;
    prepare_response(
        &cli->io,
        "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]\n",
        "food",
        cli->ai->inventory[FOOD],
        "linemate",
        cli->ai->inventory[LINEMATE],
        "deraumere",
        cli->ai->inventory[DERAUMERE],
        "sibur",
        cli->ai->inventory[SIBUR],
        "mendiane",
        cli->ai->inventory[MENDIANE],
        "phiras",
        cli->ai->inventory[PHIRAS],
        "thystame",
        cli->ai->inventory[THYSTAME]
    );
}
