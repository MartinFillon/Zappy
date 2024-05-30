/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include "types/game.h"
#include "logger.h"
#include "map.h"
#include "types/team.h"
#include "zappy.h"
#include "args_info.h"

game_t init_game(args_infos_t *ag)
{
    game_t game = {0};

    logs(INFO, "Initailizing map with size %d %d\n", ag->width, ag->height);
    game.map = create_map(ag->width, ag->height);
    fill_map(game.map);
    logs(INFO, "Map initialized successfully\n");
    logs(INFO, "Creating teams\n");
    game.teams = vec_create_vector_team_t(10);
    game.ais = vec_create_vector_ai_t(10);
    game.frequency = ag->freq;
    for (__auto_type i = 0; ag->names[i]; i++) {
        vec_pushback_vector_team_t(game.teams, create_team(ag->names[i]));
    }
    logs(INFO, "Team created successfully\n");
    return game;
}