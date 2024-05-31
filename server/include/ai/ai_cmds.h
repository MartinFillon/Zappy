/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_cmds
*/

#pragma once

#include <stdlib.h>
#include "types/client.h"

typedef struct ai_cmds_s {
    char const *name;
    void (*func)(char const *arg, client_t *, game_t *, client_t *);
} ai_cmds_t;

/**
 * @brief Handle forward command from an ai, that move an ai forward
 *        with respect with his direction.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will move.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_forward(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Rotate player's direction of 90° in right side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_rotate_right(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Rotate player's direction of 90° in left side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_rotate_left(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that is looking at environment.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_look(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that will that is looking at his
 *            inventory.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_inventory(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Send a message to all the players in the map.
 * @param arg Message to be sent.
 * @param cli Clients' informations/Ai that is broadcasting a message.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_broadcast(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Give the number of unused slot in the current ai @param cli.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that is asking for the number slot.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_connect_nbr(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Fork to add an egg to the current team.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that is asking for a new slot.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_fork(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief The ai @param cli eject all the players from his tile
 *        to the direction he is looking at
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that is ejecting everyone.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_eject(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Take an object specified in @param arg and store it in
 *        the inventory of the player
 * @param arg Name of the object to be taken.
 * @param cli Clients' informations/Ai that take an object.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_take_object(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

/**
 * @brief Drop an object specified in @param arg from player's inventory in
 *        the map.
 * @param arg Name of the object to drop.
 * @param cli Clients' informations/Ai that drop an object.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_set_object(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
);

static const ai_cmds_t AI_CMDS[] = {
    {"Forward", handle_forward},

    {"Right", handle_rotate_right},
    {"Left", handle_rotate_left},

    {"Look", handle_look},
    {"Inventory", handle_inventory},
    {"Broadcast ", handle_broadcast}, // Need the tile distance.

    {"Connect_nbr", handle_connect_nbr},
    {"Fork", handle_fork},
    {"Eject", handle_eject},

    {"Take ", handle_take_object},
    {"Set ", handle_set_object},
    // {"Incantation", NULL},

    {NULL, NULL}
};
