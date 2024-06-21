/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ai.spec
*/

#include <stdio.h>
#include <criterion/criterion.h>

#include "fake_server.h"

Test(core, unknown_ai_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    send_unknown_command(cli);
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core, move_by_dir_up)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, UP, z.game.map);
    cr_assert_eq(pos.x, 5);
    cr_assert_eq(pos.y, 4);
}

Test(core, move_by_dir_down)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, DOWN, z.game.map);
    cr_assert_eq(pos.x, 5);
    cr_assert_eq(pos.y, 6);
}

Test(core, move_by_dir_left)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, LEFT, z.game.map);
    cr_assert_eq(pos.x, 4);
    cr_assert_eq(pos.y, 5);
}

Test(core, move_by_dir_right)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, RIGHT, z.game.map);
    cr_assert_eq(pos.x, 6);
    cr_assert_eq(pos.y, 5);
}

Test(core, move_ai)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    move_ai(cli->ai, UP, z.game.map);
    cr_assert_eq(cli->ai->pos.x, 5);
    cr_assert_eq(cli->ai->pos.y, 0);
}

Test(core, handle_forward_with_gui)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Forward"));
    command_state_t com = {args, z.clients, &z.game};

    ai->ai->dir = UP;
    str_clear(cli->io.res);
    handle_forward(ai, &com);
    char *event = NULL;
    asprintf(
        &event,
        "ppo %d %d %d %d\n",
        ai->ai->id,
        ai->ai->pos.x,
        ai->ai->pos.y,
        ai->ai->dir + 1
    );
    cr_assert_str_eq(ai->io.res->data, "ok\n");
    cr_assert_str_eq(cli->io.res->data, event);
}

Test(core, rotate_left)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Left"));
    command_state_t com = {args, z.clients, &z.game};

    ai->ai->dir = UP;
    str_clear(cli->io.res);
    handle_rotate_left(ai, &com);
    char *event = NULL;
    asprintf(
        &event,
        "ppo %d %d %d %d\n",
        ai->ai->id,
        ai->ai->pos.x,
        ai->ai->pos.y,
        ai->ai->dir + 1
    );
    cr_assert_str_eq(ai->io.res->data, "ok\n");
    cr_assert_str_eq(cli->io.res->data, event);
}

Test(core, rotate_right)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Right"));
    command_state_t com = {args, z.clients, &z.game};

    ai->ai->dir = UP;
    str_clear(cli->io.res);
    handle_rotate_right(ai, &com);
    char *event = NULL;
    asprintf(
        &event,
        "ppo %d %d %d %d\n",
        ai->ai->id,
        ai->ai->pos.x,
        ai->ai->pos.y,
        ai->ai->dir + 1
    );
    cr_assert_str_eq(ai->io.res->data, "ok\n");
    cr_assert_str_eq(cli->io.res->data, event);
}
