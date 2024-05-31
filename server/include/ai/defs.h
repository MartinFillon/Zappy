/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_cmds
*/

#pragma once

#include "router/route.h"
#include "types/client.h"
#include "types/game.h"

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
void handle_forward(client_t *cli, command_state_t *s);

/**
 * @brief Rotate player's direction of 90° in right side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_rotate_right(client_t *cli, command_state_t *s);

/**
 * @brief Rotate player's direction of 90° in left side.
 * @param arg Argument of the command (It should be null).
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_rotate_left(client_t *cli, command_state_t *s);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param arg Argument of the command (It should be null)
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_look(client_t *cli, command_state_t *s);

/**
 * @brief Send a message to all the players in the map.
 * @param arg Message to be sent.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_broadcast(client_t *cli, command_state_t *s);

/**
 * @brief Take an object specified in @param arg and store it in
 *        the inventory of the player
 * @param arg Name of the object to be taken.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_take_object(client_t *cli, command_state_t *s);

/**
 * @brief Drop an object specified in @param arg from player's inventory in
 *        the map.
 * @param arg Name of the object to drop.
 * @param cli Clients' informations/Ai that will rotate.
 * @param game Game object with all the current game state.
 * @param clients All the clients connected.
 */
void handle_set_object(client_t *cli, command_state_t *s);
