/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ai.spec
*/

#include <criterion/criterion.h>

#include "fake_server.h"

Test(core, test_map_size)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("msz"));
    command_state_t com = {args, z.clients, &z.game};

    map_size(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "msz 10 10\n");
}

Test(core, test_map_content)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("bct"));
    vec_pushback_vector_str_t(args, str_snew("1"));
    vec_pushback_vector_str_t(args, str_snew("1"));
    command_state_t com = {args, z.clients, &z.game};

    map_content_tile(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "bct 1 1 0 0 0 0 0 0 0\n");
}

Test(core, test_map_content_invalid_tile)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("bct"));
    vec_pushback_vector_str_t(args, str_snew("11"));
    vec_pushback_vector_str_t(args, str_snew("11"));
    command_state_t com = {args, z.clients, &z.game};

    map_content_tile(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_time_request)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("sgt"));
    command_state_t com = {args, z.clients, &z.game};

    request_time(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sgt 100\n");
}

Test(core, test_update_time_request)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("sst"));
    vec_pushback_vector_str_t(args, str_snew("1"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    update_time(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sst 1\n");
    cr_assert_eq(z.game.frequency, 1);
    cr_assert_eq(ai->ai->clock->frequency, 1);
    cr_assert_eq(ai->ai->food_clock->frequency, 1);
}

Test(core, test_update_time_request_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("sst"));
    vec_pushback_vector_str_t(args, str_snew("100a"));
    command_state_t com = {args, z.clients, &z.game};

    update_time(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_update_time_request_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("sst"));
    vec_pushback_vector_str_t(args, str_snew("-100"));
    command_state_t com = {args, z.clients, &z.game};

    update_time(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_team_names)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("tna"));
    command_state_t com = {args, z.clients, &z.game};

    team_names(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "tna Team1\ntna Team2\n");
}

Test(core, test_player_position)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("ppo"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    player_position(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "ppo 0 5 1 2 1 Team1\n");
}

Test(core, test_player_position_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("ppo"));
    vec_pushback_vector_str_t(args, str_snew("100"));
    command_state_t com = {args, z.clients, &z.game};
    str_clear(cli->io.res);

    player_position(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_player_position_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("ppo"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    command_state_t com = {args, z.clients, &z.game};

    player_position(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_player_level)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("plv"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    player_level(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "plv 0 1");
}

Test(core, test_player_level_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("plv"));
    vec_pushback_vector_str_t(args, str_snew("100"));
    command_state_t com = {args, z.clients, &z.game};
    str_clear(cli->io.res);
    player_level(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_player_level_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("plv"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    command_state_t com = {args, z.clients, &z.game};

    player_level(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_player_inventory)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("pin"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    player_inventory(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "pin 0 5 1 10 0 0 0 0 0 0\n");
}

Test(core, test_player_inventory_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("pin"));
    vec_pushback_vector_str_t(args, str_snew("100"));
    command_state_t com = {args, z.clients, &z.game};
    str_clear(cli->io.res);
    player_inventory(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_player_inventory_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("pin"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    command_state_t com = {args, z.clients, &z.game};

    player_inventory(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}

Test(core, test_map_content_full)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("mct"));
    command_state_t com = {args, z.clients, &z.game};

    map_content_full(cli, &com);
    struct vector_str_t *res = str_split(cli->io.res, "\n");
    cr_assert_eq(res->size, z.game.map->x * z.game.map->y);
}

Test(core, test_tile_content_invalid)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("bct"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("b100"));
    command_state_t com = {args, z.clients, &z.game};

    map_content_tile(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
}
