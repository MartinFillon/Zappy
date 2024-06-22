/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** add_client
*/

#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include <criterion/criterion.h>

#include "core/client.h"
#include "core/router/router.h"
#include "core/server.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/team.h"
#include "zappy.h"
#include "args_info.h"

void default_args(args_infos_t *args)
{
    args->port = 4242;
    args->width = 10;
    args->height = 10;
    args->freq = 100;
    args->names = vec_create_vector_str_t(10);
    args->clients_nb = 10;

    vec_pushback_vector_str_t(args->names, str_snew("Team1"));
    vec_pushback_vector_str_t(args->names, str_snew("Team2"));
}

void init_server(zappy_t *z)
{
    args_infos_t args;

    default_args(&args);
    z->server.router = init_router();
    cr_assert_not_null(z->server.router);
    z->game = init_game(&args);
    cr_assert_not_null(z->game.map);
    cr_assert_not_null(z->game.teams);
    cr_assert_not_null(z->game.ais);
    cr_assert_not_null(z->game.clock);
    z->clients = vec_create_client_list(10);
    cr_assert_not_null(z->clients);
}

client_t *new_fake_client()
{
    int fd = -1;

    return init_client(fd, "localhost", 0);
}

client_t *new_fake_ai_client(
    team_t *test_team,
    game_t *test_game,
    struct client_list *lst
)
{
    client_t *client = new_fake_client();

    cr_assert_not_null(client);
    client->type = AI;
    cr_assert_eq(init_ai(test_game, client, test_team, lst), false);
    vec_pushback_client_list(lst, client);
    return client;
}

client_t *new_fake_gui_client(struct client_list *lst)
{
    client_t *client = new_fake_client();

    cr_assert_not_null(client);
    client->type = GUI;
    vec_pushback_client_list(lst, client);
    cr_assert_neq(lst->size, 0);
    return client;
}
