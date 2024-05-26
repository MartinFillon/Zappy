/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include "types/game.h"
#include "map.h"
#include "team.h"
#include "types/team.h"
#include "args_info.h"

game_t init_game(args_infos_t *args)
{
    game_t game = {0};
    team_t nw = {0};

    game.map = create_map(args->width, args->height);
    fill_map(game.map);
    for (__auto_type i = 0; args->names[i]; i++) {
        nw = create_team(args->names[i]);
        push_back_vector_team(game.teams, &nw);
    }

    return game;
}
