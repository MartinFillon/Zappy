/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** middlewares
*/

#pragma once

#include "core/types/client.h"

/**
 * @brief Send a message to the client when he send an invalid argument
 * @param c
 */
void send_invalid_args(client_t *c);

/**
 * @brief Send a message to the client when he send an invalid command
 * @param c
 */
void send_unknown_command(client_t *c);
