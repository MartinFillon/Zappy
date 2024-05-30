/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** defs
*/

#pragma once

#include "types/client.h"
#include "types/game.h"

typedef struct gui_cmd_s {
    char *cmd;
    void (*func)(char *, client_t *, game_t *, client_t *);
} gui_cmd_t;

void map_size(char *args, client_t *cli, game_t *g, client_t *clients);
void map_content_tile(char *args, client_t *c, game_t *g, client_t *clients);
void map_content_full(char *args, client_t *c, game_t *g, client_t *clients);
void team_names(char *args, client_t *c, game_t *g, client_t *clients);
void player_position(char *args, client_t *c, game_t *g, client_t *clients);
void player_level(char *args, client_t *c, game_t *g, client_t *clients);
void player_inventory(char *args, client_t *c, game_t *g, client_t *clients);
void update_time(char *args, client_t *c, game_t *g, client_t *clients);
void request_time(char *args, client_t *c, game_t *g, client_t *clients);
