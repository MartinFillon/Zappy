/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** defs
*/

#pragma once

#include "core/router/route.h"
#include "core/types/client.h"

/**
 * @brief Retrieve the size of the map.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void map_size(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the content of a tile.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void map_content_tile(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the content of the whole map.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void map_content_full(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the team names.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void team_names(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the player position.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void player_position(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the player level.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void player_level(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the player inventory.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void player_inventory(client_t *c, command_state_t *s);

/**
 * @brief update the frequency of the server.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void update_time(client_t *c, command_state_t *s);

/**
 * @brief Retrieve the frequency of the server.
 * @param cli Clients' informations/Ai that drop an object.
 * @param s state of the program.
 */
void request_time(client_t *c, command_state_t *s);
