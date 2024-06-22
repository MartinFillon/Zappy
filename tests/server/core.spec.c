/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** core.spec
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "fake_server.h"

void redirect(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(core, clock)
{
    zclock_t *clock = clock_new(100);

    cr_assert_not_null(clock);
    cr_assert_eq(clock->frequency, 10000);

    cr_assert_eq(has_n_ticks_passed(clock, 1), false);
    clock->start = clock->start - 1000000;
    cr_assert_eq(has_n_ticks_passed(clock, 1), true);
}

Test(core, clock_wait)
{
    zclock_t *clock = clock_new(100);

    cr_assert_not_null(clock);
    cr_assert_eq(clock->frequency, 10000);

    wait_n_ticks(clock, 3);

    cr_assert_eq(has_n_ticks_passed(clock, 3), true);
}

Test(core, clock_reset)
{
    zclock_t *clock = clock_new(100);

    cr_assert_not_null(clock);
    cr_assert_eq(clock->frequency, 10000);

    wait_n_ticks(clock, 3);

    cr_assert_eq(has_n_ticks_passed(clock, 3), true);

    reset_clock(clock);

    cr_assert_eq(has_n_ticks_passed(clock, 3), false);
}

Test(core, clock_elapsed_time)
{
    zclock_t *clock = clock_new(100);

    cr_assert_not_null(clock);
    cr_assert_eq(clock->frequency, 10000);

    wait_n_ticks(clock, 3);

    cr_assert_geq(get_elapsed_time(clock), 30000);
}

Test(core, current_tick)
{
    zclock_t *clock = clock_new(100);

    cr_assert_not_null(clock);
    cr_assert_eq(clock->frequency, 10000);

    wait_n_ticks(clock, 3);

    cr_assert_eq(current_tick(clock), 3);
}

Test(core, invalid_command_unset)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_client();

    run_router(z.server.router, cli, &z, str_snew("invalid"));
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core, invalid_command_gui)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);

    run_router(z.server.router, cli, &z, str_snew("invalid\n"));
    cr_assert_str_eq(cli->io.res->data, "suc\n");
}

Test(core, invalid_command_ai)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    run_router(z.server.router, cli, &z, str_snew("invalid\n"));
    cr_assert_str_eq(cli->io.res->data, "ko\n");
    destroy_router(z.server.router);
}

Test(core, new_ai_with_multiple_guis)
{
    zappy_t z;
    client_t *clis[3] = {0};

    init_server(&z);
    for (int i = 0; i < 3; i++)
        clis[i] = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    cr_assert_not_null(ai);
    for (int i = 0; i < 3; i++)
        cr_assert_str_eq(clis[i]->io.res->data, "ebo 0\npnw 0 5 1 2 1 Team1\n");
}

Test(core, run_gui_command_through_router)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);

    run_router(z.server.router, cli, &z, str_snew("msz"));
    cr_assert_str_eq(cli->io.res->data, "msz 10 10\n");
    destroy_router(z.server.router);
}

Test(core, run_ai_command_through_router)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    run_router(z.server.router, cli, &z, str_snew("Forward"));
    cr_assert_str_eq(cli->io.res->data, "ok\n");
    cr_assert_eq(cli->ai->cycles_to_wait, 7);
    destroy_router(z.server.router);
}

Test(core, gui_router_too_much_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);

    run_router(z.server.router, cli, &z, str_snew("msz 1 2"));
    cr_assert_str_eq(cli->io.res->data, "sbp\n");
    destroy_router(z.server.router);
}

Test(core, ai_router_too_much_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    run_router(z.server.router, cli, &z, str_snew("Forward 1"));
    cr_assert_str_eq(cli->io.res->data, "ko\n");
    destroy_router(z.server.router);
}

Test(core, run_router_empty_str)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);

    run_router(z.server.router, cli, &z, str_snew(""));
    cr_assert_str_eq(cli->io.res->data, "");
    destroy_router(z.server.router);
}

Test(core, execute_two_ai_commands)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    cr_assert_eq(z.clients->size, 1);
    queue_pushback_queue_command_t(cli->commands, str_snew("Forward"));
    queue_pushback_queue_command_t(cli->commands, str_snew("Forward"));
    execute_commands(&z);
    execute_commands(&z);
    wait_n_ticks(cli->ai->clock, cli->ai->cycles_to_wait);
    execute_commands(&z);
    cr_assert_str_eq(cli->io.res->data, "ok\nok\n");
    destroy_router(z.server.router);
}

Test(core, execute_gui_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);

    cr_assert_eq(z.clients->size, 1);
    queue_pushback_queue_command_t(cli->commands, str_snew("msz"));
    execute_commands(&z);
    cr_assert_str_eq(cli->io.res->data, "msz 10 10\n");
    destroy_router(z.server.router);
}

Test(core, godmode_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(2);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));

    godmode(&z, args);
    cr_assert_eq(cli->ai->godmode, true);
    godmode(&z, args);
    cr_assert_eq(cli->ai->godmode, false);
}

Test(core, godmode_command_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("a"));

    godmode(&z, args);
    cr_assert_eq(cli->ai->godmode, false);
}

Test(core, godmode_command_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("100"));

    godmode(&z, args);
    cr_assert_eq(cli->ai->godmode, false);
}

Test(core, kill_player_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));

    handle_kill_player(&z, args);
    cr_assert_eq(z.game.ais->size, 0);
}

Test(core, kill_player_command_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("a"));

    handle_kill_player(&z, args);
    cr_assert_eq(z.game.ais->size, 1);
}

Test(core, kill_player_command_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("100"));

    handle_kill_player(&z, args);
    cr_assert_eq(z.game.ais->size, 1);
}

Test(core, display_map_command_no_player, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("display_map"));

    handle_display_map(&z, args);
    cr_assert_stdout_neq_str("");
}

Test(core, give_player_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(4);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("LINEMATE"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    give(&z, args);
    cr_assert_eq(cli->ai->inventory[LINEMATE], 1);
}

Test(core, give_player_command_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(4);
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("LINEMATE"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    give(&z, args);
    cr_assert_eq(cli->ai->inventory[LINEMATE], 0);
}

Test(core, give_player_command_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(4);
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("LINEMATE"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    give(&z, args);
    cr_assert_eq(cli->ai->inventory[LINEMATE], 0);
}

Test(core, give_player_command_invalid_args3)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(4);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("LINEMATE"));
    vec_pushback_vector_str_t(args, str_snew("a"));

    give(&z, args);
    cr_assert_eq(cli->ai->inventory[LINEMATE], 0);
}

Test(core, give_player_command_invalid_args4)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(4);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("youpi dansons la carioca"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    give(&z, args);
    cr_assert_eq(cli->ai->inventory[LINEMATE], 0);
}

Test(core, help_command, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("help"));

    handle_help(&z, args);
    cr_assert_stdout_neq_str("");
}

Test(core, teleport_player_to_player)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    teleport(&z, args);
    cr_assert_eq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_eq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, teleport_player_to_player_invalid_args)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("a"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    teleport(&z, args);
    cr_assert_neq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_neq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, teleport_player_to_player_invalid_args2)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("4"));
    vec_pushback_vector_str_t(args, str_snew("1"));

    teleport(&z, args);
    cr_assert_neq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_neq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, teleport_player_to_player_invalid_args3)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("a"));

    teleport(&z, args);
    cr_assert_neq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_neq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, teleport_player_to_player_invalid_args4)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("0"));
    vec_pushback_vector_str_t(args, str_snew("youpi dansons la carioca"));

    teleport(&z, args);
    cr_assert_neq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_neq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, teleport_player_to_player_invalid_args5)
{
    zappy_t z;

    init_server(&z);
    client_t *cli1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *cli2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(3);
    vec_pushback_vector_str_t(args, str_snew("100"));
    vec_pushback_vector_str_t(args, str_snew("4"));
    vec_pushback_vector_str_t(args, str_snew("42"));

    teleport(&z, args);
    cr_assert_neq(cli1->ai->pos.x, cli2->ai->pos.x);
    cr_assert_neq(cli1->ai->pos.y, cli2->ai->pos.y);
}

Test(core, get_egss_infos, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("display_eggs"));

    handle_display_eggs(&z, args);

    cr_assert_stdout_neq_str("");
}

Test(core, command_runner_invalid_arg, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    handle_server_cmd("/tp", &z);
    cr_assert_stderr_neq_str("");
}

Test(core, command_runner_empty_string, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    handle_server_cmd("", &z);
    cr_assert_stderr_eq_str("");
}

Test(core, unknown_command, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    handle_server_cmd("unknown", &z);
    cr_assert_stderr_neq_str("");
}

Test(core, command_runner_success, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    handle_server_cmd("/help", &z);
    cr_assert_stderr_eq_str("");
    cr_assert_stdout_neq_str("");
}

Test(core, display_ai_info, .init = redirect)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("/ais"));

    handle_display_ais(&z, args);
    char *res = NULL;

    ai_t *ai = cli->ai;
    asprintf(
        &res,
        "AI [%d][Team: %s] (%s) pos (%d, %d) | level %ld\n",
        ai->id,
        ai->team->name,
        ai->alive ? "alive" : "dead",
        ai->pos.y,
        ai->pos.x,
        ai->level
    );
    cr_assert_stdout_eq_str(res);
}

Test(core, display_ai_info_no_ai, .init = redirect)
{
    zappy_t z;

    init_server(&z);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("/ais"));

    handle_display_ais(&z, args);
    cr_assert_stdout_eq_str("");
}

Test(core, display_ai_ressources, .init = redirect)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("/ais-res"));

    handle_ressources_ais(&z, args);
    char *res = NULL;

    ai_t *ai = cli->ai;
    asprintf(
        &res,
        "AI [%d][Team: %s] (%s)\n"
        "Ressources: %lu %lu %lu %lu %lu %lu %lu\n",
        ai->id,
        ai->team->name,
        ai->alive ? "alive" : "dead",
        ai->inventory[FOOD],
        ai->inventory[LINEMATE],
        ai->inventory[DERAUMERE],
        ai->inventory[SIBUR],
        ai->inventory[MENDIANE],
        ai->inventory[PHIRAS],
        ai->inventory[THYSTAME]
    );
    cr_assert_stdout_eq_str(res);
}

Test(core, buffer_handling)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_client();

    for (int i = 0; i < 10; i++)
        str_sadd(cli->io.req, str_snew("msz\n"));
    cr_assert_eq(cli->io.req->size, 10 * 4);
    str_sadd(cli->io.req, str_snew("msz"));
    handle_buffer(cli);
    cr_assert_eq(cli->io.req->size, 3);
    cr_assert_eq(cli->commands->size, 10);
    for (int i = 0; i < 10; i++)
        cr_assert_str_eq(cli->commands->data[i]->data, "msz");

    cr_assert_str_eq(cli->io.req->data, "msz");
}

Test(core, empty_buffer_handling)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_client();

    handle_buffer(cli);
    cr_assert_eq(cli->io.req->size, 0);
    cr_assert_eq(cli->commands->size, 0);
}

Test(core, online_buffer_handling)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_client();

    str_sadd(cli->io.req, str_snew("msz\n"));
    handle_buffer(cli);
    cr_assert_eq(cli->io.req->size, 0);
    cr_assert_eq(cli->commands->size, 1);
    cr_assert_str_eq(cli->commands->data[0]->data, "msz");
}
