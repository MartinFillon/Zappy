/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** middlewares
*/

#pragma once

#include "core/types/client.h"

void send_invalid_args(client_t *c);
void send_unknown_command(client_t *c);
