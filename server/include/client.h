/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include "types/client.h"

void init_client(client_t *c, int fd);

void send_client(client_t *client, char *fmt, ...);
int read_client(client_t *client);
int ai_entrypoint(char const *line, client_t *c, game_t *game);
int gui_entrypoint(char const *line, client_t *c, game_t *game);
int unset_entrypoint(char const *line, client_t *c, game_t *game);
void close_client(client_t *c);
