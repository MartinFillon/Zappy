/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** defs
*/

#pragma once

#include "router/route.h"
#include "types/client.h"

void map_size(client_t *c, command_state_t *s);
void map_content_tile(client_t *c, command_state_t *s);
void map_content_full(client_t *c, command_state_t *s);
void team_names(client_t *c, command_state_t *s);
void player_position(client_t *c, command_state_t *s);
void player_level(client_t *c, command_state_t *s);
void player_inventory(client_t *c, command_state_t *s);
void update_time(client_t *c, command_state_t *s);
void request_time(client_t *c, command_state_t *s);
