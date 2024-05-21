/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include "types/client.h"

void init_client(client_t *c);

int ai_entrypoint(char const *line, client_t *c, game_t *game);
int gui_entrypoint(char const *line, client_t *c, game_t *game);
int unset_entrypoint(char const *line, client_t *c, game_t *game);
