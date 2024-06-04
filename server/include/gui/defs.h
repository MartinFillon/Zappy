/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** defs
*/

#pragma once

#include "router/route.h"
#include "types/client.h"

void map_size(client_t *c, command_state_t *com);
void map_content_tile(client_t *c, command_state_t *com);
void map_content_full(client_t *c, command_state_t *com);
void team_names(client_t *c, command_state_t *com);
void player_position(client_t *c, command_state_t *com);
void player_level(client_t *c, command_state_t *com);
void player_inventory(client_t *c, command_state_t *com);
void update_time(client_t *c, command_state_t *com);
void request_time(client_t *c, command_state_t *com);
