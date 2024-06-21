/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fake_server
*/

#pragma once

#include "core/server.h"
#include "core/types/client.h"
#include "core/types/game.h"

client_t *new_fake_client();
client_t *new_fake_ai_client(
    team_t *test_team,
    game_t *test_game,
    struct client_list *lst
);
client_t *new_fake_gui_client(struct client_list *lst);
void close_client_test(client_t *client, zappy_t *z, int i);
void init_server(zappy_t *z);
