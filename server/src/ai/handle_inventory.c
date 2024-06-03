/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_inventory
*/

#include "router/route.h"
#include "types/ai.h"
#include "types/client.h"
#include "client.h"

void handle_inventory(client_t *cli, command_state_t *s)
{
    inventory_t *inv = &cli->ai->inventory;

    (void) s;
    prepare_response(&cli->io,
        "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]\n",
        "food", inv->food,
        "linemate", inv->linemate,
        "deraumere", inv->deraumere,
        "sibur", inv->sibur,
        "mendiane", inv->mendiane,
        "phiras", inv->phiras,
        "thystame", inv->thystame
    );
}
