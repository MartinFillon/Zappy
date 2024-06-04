/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include "types/game.h"
#include "client.h"
#include "clock.h"
#include "logger.h"
#include "map.h"
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
        vec_pushback_vector_team_t(game.teams, create_team(ag, ag->names[i]));
    }
    logs(INFO, "Team created successfully\n");
    game.clock = clock_new(ag->freq);
    return game;
}

void destroy_game(game_t *game)
{
    destroy_map(game->map);
    vec_foreach_vector_team_t(game->teams, &destroy_team);
    vec_destroy_vector_team_t(game->teams);
    vec_foreach_vector_ai_t(game->ais, &destroy_ai);
    vec_destroy_vector_ai_t(game->ais);
    free(game->clock);
}
