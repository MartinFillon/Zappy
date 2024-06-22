/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fake_server
*/

#pragma once

#include "core/ai/defs.h"
#include "core/clock.h"
#include "core/gui/defs.h"
#include "core/middlewares.h"
#include "core/router/route.h"
#include "core/router/router.h"
#include "core/server.h"
#include "core/types/client.h"
#include "core/types/clock.h"
#include "core/types/game.h"
#include "core/types/object.h"
#include "logger.h"
#include "queue.h"
#include "str.h"
#include "zappy.h"
#include "core/serv_cmd/serv_cmds.h"

client_t *new_fake_client();
client_t *new_fake_ai_client(
    team_t *test_team,
    game_t *test_game,
    struct client_list *lst
);
client_t *new_fake_gui_client(struct client_list *lst);
void close_client_test(client_t *client, zappy_t *z, int i);
void init_server(zappy_t *z);
