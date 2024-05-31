/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_inventory
*/

#include "types/ai.h"
#include "types/client.h"
#include "client.h"
#include "utils.h"

void handle_inventory(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    inventory_t *inv = &cli->ai->inventory;

    (void) game;
    (void) clients;
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
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
