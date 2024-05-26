/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include "types/game.h"
#include "map.h"
#include "team.h"
#include "utils.h"
#include "args_info.h"

game_t init_game(args_infos_t *args)
{
    game_t game = {0};
    team_t nw = {0};

    logger_info(
        "Initailizing map with size %d %d\n", args->width, args->height
    );
    game.map = create_map(args->width, args->height);
    fill_map(game.map);
    logger_info("Map initialized successfully\n");
    logger_info("Creating teams\n");
    game.teams = init_teams(1);
    for (__auto_type i = 0; args->names[i]; i++) {
        logger_debug("Creating %s\n", args->names[i]);
        nw = create_team(args->names[i]);
        logger_debug("Pushing %s\n", nw.name);
        push_back_vector_team(game.teams, &nw);
    }
    logger_info("Team created successfully\n");
    return game;
}
