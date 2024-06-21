/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ai.spec
*/

#include <stdio.h>
#include <criterion/criterion.h>
#include "core/types/client.h"
#include "core/types/object.h"

#include "fake_server.h"

Test(core_ai, unknown_ai_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    send_unknown_command(cli);
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core_ai, move_by_dir_up)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, UP, z.game.map);
    cr_assert_eq(pos.x, 5);
    cr_assert_eq(pos.y, 4);
}

Test(core_ai, move_by_dir_down)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, DOWN, z.game.map);
    cr_assert_eq(pos.x, 5);
    cr_assert_eq(pos.y, 6);
}

Test(core_ai, move_by_dir_left)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, LEFT, z.game.map);
    cr_assert_eq(pos.x, 4);
    cr_assert_eq(pos.y, 5);
}

Test(core_ai, move_by_dir_right)
{
    zappy_t z;

    init_server(&z);

    pos_t pos = {5, 5};

    move_by_dir(&pos, RIGHT, z.game.map);
    cr_assert_eq(pos.x, 6);
    cr_assert_eq(pos.y, 5);
}

Test(core_ai, move_ai)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    move_ai(cli->ai, UP, z.game.map);
    cr_assert_eq(cli->ai->pos.x, 5);
    cr_assert_eq(cli->ai->pos.y, 0);
}

Test(core_ai, handle_forward_with_gui)
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

Test(core_ai, rotate_left)
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

Test(core_ai, rotate_right)
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

Test(core_ai, connect_nbr)
{
    zappy_t z;

    init_server(&z);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Right"));
    command_state_t com = {args, z.clients, &z.game};

    char *res = NULL;
    handle_connect_nbr(ai, &com);
    asprintf(&res, "%ld\n", ai->ai->team->eggs->size);
    cr_assert_str_eq(ai->io.res->data, res);
}

Test(core_ai, inventory)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("quoi"));
    command_state_t com = {args, z.clients, &z.game};

    char *res = NULL;
    handle_inventory(cli, &com);
    asprintf(
        &res,
        "[%s %ld, %s %ld, %s %ld, %s %ld, %s %ld, %s %ld, %s %ld]\n",
        "food",
        cli->ai->inventory[FOOD],
        "linemate",
        cli->ai->inventory[LINEMATE],
        "deraumere",
        cli->ai->inventory[DERAUMERE],
        "sibur",
        cli->ai->inventory[SIBUR],
        "mendiane",
        cli->ai->inventory[MENDIANE],
        "phiras",
        cli->ai->inventory[PHIRAS],
        "thystame",
        cli->ai->inventory[THYSTAME]
    );
    cr_assert_str_eq(cli->io.res->data, res);
}

Test(core_ai, take_object)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Take"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME] = 1;

    handle_take_object(cli, &com);
    cr_assert_eq(cli->ai->inventory[THYSTAME], 1);
    cr_assert_eq(
        z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME], 0
    );
    cr_assert_str_eq(cli->io.res->data, "ok\n");
}

Test(core_ai, take_object_fail)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Take"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME] = 0;

    handle_take_object(cli, &com);
    cr_assert_eq(cli->ai->inventory[THYSTAME], 0);
    cr_assert_eq(
        z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME], 0
    );
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core_ai, take_object_invalid)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Take"));
    vec_pushback_vector_str_t(args, str_snew("invalid"));
    command_state_t com = {args, z.clients, &z.game};

    handle_take_object(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core_ai, take_object_with_gui)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Take"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    z.game.map->arena[ai->ai->pos.y][ai->ai->pos.x].content[THYSTAME] = 1;

    str_clear(cli->io.res);
    handle_take_object(ai, &com);
    char *event = NULL;
    asprintf(&event, "pgt %d %d\n", ai->ai->id, THYSTAME);
    cr_assert_str_eq(ai->io.res->data, "ok\n");
    cr_assert_str_eq(cli->io.res->data, event);
}

Test(core_ai, set_object)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Set"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    cli->ai->inventory[THYSTAME] = 1;

    handle_set_object(cli, &com);
    cr_assert_eq(cli->ai->inventory[THYSTAME], 0);
    cr_assert_eq(
        z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME], 1
    );
    cr_assert_str_eq(cli->io.res->data, "ok\n");
}

Test(core_ai, set_object_fail)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Set"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    cli->ai->inventory[THYSTAME] = 0;

    handle_set_object(cli, &com);
    cr_assert_eq(cli->ai->inventory[THYSTAME], 0);
    cr_assert_eq(
        z.game.map->arena[cli->ai->pos.y][cli->ai->pos.x].content[THYSTAME], 0
    );
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core_ai, set_object_invalid)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Set"));
    vec_pushback_vector_str_t(args, str_snew("invalid"));
    command_state_t com = {args, z.clients, &z.game};

    handle_set_object(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "ko\n");
}

Test(core_ai, set_object_with_gui)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Set"));
    vec_pushback_vector_str_t(args, str_snew("thystame"));
    command_state_t com = {args, z.clients, &z.game};

    ai->ai->inventory[THYSTAME] = 1;

    str_clear(cli->io.res);
    handle_set_object(ai, &com);
    char *event = NULL;
    asprintf(&event, "pdr %d %d\n", ai->ai->id, THYSTAME);
    cr_assert_str_eq(ai->io.res->data, "ok\n");
    cr_assert_str_eq(cli->io.res->data, event);
}

Test(core_ai, look)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Look"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    handle_look(cli, &com);
    cr_assert_str_eq(
        cli->io.res->data,
        "[player deraumere,linemate thystame,food linemate thystame,food "
        "phiras]\n"
    );
}

Test(core_ai, fork)
{
    zappy_t z;

    init_server(&z);
    client_t *cli =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Fork"));
    command_state_t com = {args, z.clients, &z.game};

    size_t old = z.game.teams->data[0].eggs->size;
    str_clear(cli->io.res);
    handle_fork(cli, &com);
    cr_assert_str_eq(cli->io.res->data, "ok\n");
    cr_assert_eq(z.game.teams->data[0].eggs->size, old + 1);
}

Test(core_ai, fork_with_gui)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Fork"));
    command_state_t com = {args, z.clients, &z.game};

    size_t old = z.game.teams->data[0].eggs->size;
    str_clear(cli->io.res);
    handle_fork(ai, &com);
    char *event = NULL;
    asprintf(
        &event,
        "pfk %d\nenw %ld %d %d %d\n",
        ai->ai->id,
        z.game.teams->data[0]
            .eggs->data[z.game.teams->data[0].eggs->size - 1]
            ->id,
        ai->ai->id,
        ai->ai->pos.x,
        ai->ai->pos.y
    );
    cr_assert_str_eq(cli->io.res->data, event);
    cr_assert_eq(z.game.teams->data[0].eggs->size, old + 1);
}

Test(core_ai, eject_no_egg)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *ai2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    ai1->ai->dir = UP;
    handle_server_cmd("/tp 0 1", &z);
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Eject"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    handle_eject(ai1, &com);
    cr_assert_str_eq(ai1->io.res->data, "ok\n");
    cr_assert_str_eq(ai2->io.res->data, "eject: 1\n");
    struct vector_str_t *res = str_split(cli->io.res, "\n");
    cr_assert_str_eq(res->data[0]->data, "ppo 1 9 8 2");
    cr_assert_str_eq(res->data[1]->data, "pex 0");
}

Test(core_ai, eject_with_egg)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *ai2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    ai1->ai->dir = UP;
    handle_server_cmd("/tp 0 1", &z);
    struct vector_str_t *argsf = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(argsf, str_snew("Fork"));

    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Eject"));
    command_state_t com = {args, z.clients, &z.game};
    command_state_t comf = {argsf, z.clients, &z.game};

    handle_fork(ai1, &comf);
    str_clear(cli->io.res);
    handle_eject(ai1, &com);

    char *egg_dead = NULL;
    asprintf(
        &egg_dead,
        "edi %ld",
        ai1->ai->team->eggs->data[ai1->ai->team->eggs->size]->id
    );
    cr_assert_str_eq(ai1->io.res->data, "ok\nok\n");
    cr_assert_str_eq(ai2->io.res->data, "eject: 1\n");
    struct vector_str_t *res = str_split(cli->io.res, "\n");
    cr_assert_str_eq(res->data[0]->data, "ppo 1 9 8 2");
    cr_assert_str_eq(res->data[1]->data, egg_dead);
    cr_assert_str_eq(res->data[2]->data, "pex 0");
}

Test(core_ai, broadcast_command)
{
    zappy_t z;

    init_server(&z);
    client_t *cli = new_fake_gui_client(z.clients);
    client_t *ai1 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *ai2 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *ai3 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);
    client_t *ai4 =
        new_fake_ai_client(&z.game.teams->data[0], &z.game, z.clients);

    ai4->ai->pos.x = 1;
    ai4->ai->pos.y = 1;
    struct vector_str_t *args = vec_create_vector_str_t(1);
    vec_pushback_vector_str_t(args, str_snew("Broadcast"));
    vec_pushback_vector_str_t(args, str_snew("Hello"));
    command_state_t com = {args, z.clients, &z.game};

    str_clear(cli->io.res);
    handle_broadcast(ai1, &com);
    cr_assert_str_eq(ai1->io.res->data, "ok\n");
    cr_assert_str_eq(ai2->io.res->data, "message 6, Hello\n");
    cr_assert_str_eq(ai3->io.res->data, "message 5, Hello\n");
    cr_assert_str_eq(ai4->io.res->data, "message 7, Hello\n");
    cr_assert_str_eq(cli->io.res->data, "pbc 0 Hello\n");
}
