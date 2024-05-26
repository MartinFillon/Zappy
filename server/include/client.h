/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include "server.h"
#include "types/client.h"

void init_client(client_t *c, int fd);

void send_client(client_t *client, char *fmt, ...);
int read_client(client_t *client);
int ai_entrypoint(char const *line, client_t *c, game_t *game);
int gui_entrypoint(char const *line, client_t *c, game_t *game);
int unset_entrypoint(char const *line, client_t *c, game_t *game);
void close_client(client_t *c);
void make_ai_eat(client_t *cli, server_t *server, int n);
bool init_ai(game_t *game, client_t *client, team_t const *team);
