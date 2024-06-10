/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_cmds
*/

#pragma once

#include "core/router/route.h"
#include "core/types/client.h"

typedef struct ai_cmds_s {
    char const *name;
    void (*func)(client_t *cli, command_state_t *s);
} ai_cmds_t;

/**
 * @brief Handle forward command from an ai, that move an ai forward
 *        with respect with his direction.
 * @param cli Clients' informations/Ai that will move.
 * @param s state of the program.
 */
void handle_forward(client_t *cli, command_state_t *s);

/**
 * @brief Rotate player's direction of 90° in right side.
 * @param cli Clients' informations/Ai that will rotate.
 * @param s state of the program.
 */
void handle_rotate_right(client_t *cli, command_state_t *s);

/**
 * @brief Rotate player's direction of 90° in left side.
 * @param cli Clients' informations/Ai that will rotate.
 * @param s state of the program.
 */
void handle_rotate_left(client_t *cli, command_state_t *s);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param cli Clients' informations/Ai that is looking at environment.
 * @param s state of the program.
 */
void handle_look(client_t *cli, command_state_t *s);

/**
 * @brief Look at tiles in front of the player and send it.
 * @param cli Clients' informations/Ai that will that is looking at his
 *            inventory.
 * @param s state of the program.
 */
void handle_inventory(client_t *cli, command_state_t *s);

/**
 * @brief Send a message to all the players in the map.
 * @param cli Clients' informations/Ai that is broadcasting a message.
 * @param s state of the program.
 */
void handle_broadcast(client_t *cli, command_state_t *s);

/**
 * @brief Give the number of unused slot in the current ai @param cli.
 * @param cli Clients' informations/Ai that is asking for the number slot.
 * @param s state of the program.
 */
void handle_connect_nbr(client_t *cli, command_state_t *s);

/**
 * @brief Fork to add an egg to the current team.
 * @param cli Clients' informations/Ai that is asking for a new slot.
 * @param s state of the program.
 */
void handle_fork(client_t *cli, command_state_t *s);

/**
 * @brief The ai @param cli eject all the players from his tile
 *        to the direction he is looking at
 * @param cli Clients' informations/Ai that is ejecting everyone.
 * @param s state of the program.
 */
void handle_eject(client_t *cli, command_state_t *s);

/**
 * @brief Take an object specified in args variable of structure @param s
 *        and store it in the inventory of the player
 * @param cli Clients' informations/Ai that take an object.
 * @param s state of the program.
 */
void handle_take_object(client_t *cli, command_state_t *s);

/**
 * @brief Drop an object specified in args variable of structure @param s
 *        from player's inventory in the map.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void handle_set_object(client_t *cli, command_state_t *s);

/**
 * @brief Start the incantation in the ai inside the @param cli argument.
 * @param cli Clients' informations/Ai that start incantation.
 * @param s state of the program.
 */
void handle_start_incantation(client_t *cli, command_state_t *s);

/**
 * @brief Ending of the incantation started with @ref handle_start_incantation
 * @param cli Clients' informations/Ai whose incantation ends.
 * @param s state of the program.
 */
void handle_end_incantation(client_t *cli, command_state_t *s);
