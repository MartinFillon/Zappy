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
    void (*func)(char const *arg, client_t *, game_t *);
} ai_cmds_t;

/**
 * @brief Handle forward command from an ai, that move an ai forward
 *        with respect with his direction.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will move.
 * @param game Game object with all the current game state.
 *
 */
void handle_forward(char const *arg, client_t *cli, game_t *game);

/**
 * @brief Rotate player's direction of 90° in right side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_rotate_right(char const *arg, client_t *cli, game_t *game);


/**
 * @brief Rotate player's direction of 90° in left side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_rotate_left(char const *arg, client_t *cli, game_t *game);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_look(char const *arg, client_t *cli, game_t *game);

/**
 * @brief Send a message to all the players in the map.
 * @param arg Message to be sent.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_broadcast(char const *arg, client_t *cli, game_t *game);

/**
 * @brief Take an object specified in @param arg and store it in
 *        the inventory of the player
 * @param arg Name of the object to be taken.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_take_object(char const *arg, client_t *cli, game_t *game);

/**
 * @brief Drop an object specified in @param arg from player's inventory in
 *        the map.
 * @param arg Name of the object to drop.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 *
 */
void handle_set_object(char const *arg, client_t *cli, game_t *game);

static const ai_cmds_t AI_CMDS[] = {
    {"Forward", handle_forward},

    {"Right", handle_rotate_right},
    {"Left", handle_rotate_left},

    {"Look", handle_look},
    // {"Inventory", NULL},
    {"Broadcast ", handle_broadcast},

    // {"Connect_nbr", NULL},
    // {"Fork", NULL},
    // {"Eject", NULL},

    {"Take ", handle_take_object},
    {"Set ", handle_set_object},
    // {"Incantation", NULL},

    {NULL, NULL}
};
