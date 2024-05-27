/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include "types/game.h"
#include "map.h"
#include "types/team.h"
#include "utils.h"
#include "zappy.h"
#include "args_info.h"

game_t init_game(args_infos_t *args)
{
    game_t game = {0};

    logger_info(
        "Initailizing map with size %d %d\n", args->width, args->height
    );
    game.map = create_map(args->width, args->height);
    fill_map(game.map);
    logger_info("Map initialized successfully\n");
    logger_info("Creating teams\n");
    game.teams = vec_create_vector_team_t(10);
    game.ais = vec_create_vector_ai_t(10);
    game.frequency = args->freq;
    for (__auto_type i = 0; args->names[i]; i++) {
        vec_pushback_vector_team_t(game.teams, create_team(args->names[i]));
    }
    logger_info("Team created successfully\n");
    return game;
}