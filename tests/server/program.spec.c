/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** program.spec
*/

#include <criterion/criterion.h>

#include "core/server.h"
#include "macros.h"
#include "str.h"
#include "zappy.h"
#include "args_info.h"

Test(program, successfull_init)
{
    int client_nb = 10;
    int port = 4242;
    int width = 10;
    int height = 10;
    int freq = 100;
    char *names[] = {"toto", "tata", NULL};
    size_t i = 0;

    zappy_t z;
    args_infos_t args = {
        .clients_nb = client_nb,
        .port = port,
        .width = width,
        .height = height,
        .freq = freq,
        .names = vec_create_vector_str_t(10),
    };

    for (; names[i]; i++) {
        vec_pushback_vector_str_t(args.names, str_snew(names[i]));
    }

    cr_assert_eq(init_program(&args, &z), SUCCESS);
    cr_assert_neq(z.server.fd, -1);
    cr_assert_not_null(z.server.router);
    cr_assert_not_null(z.game.map);
    cr_assert_not_null(z.clients);
    cr_assert_eq(z.clients->size, 0);
    cr_assert_eq(z.clients->capacity, 10);
    cr_assert_eq(z.game.map->x, width);
    cr_assert_eq(z.game.map->y, height);
    cr_assert_not_null(z.game.teams);
    cr_assert_not_null(z.game.map->arena);
    cr_assert_eq(z.game.teams->size, i);
    cr_assert_eq(z.game.frequency, freq);
    for (size_t k = 0; k < z.game.teams->size; k++) {
        cr_assert_not_null(z.game.teams->data[k].name);
        cr_assert_str_eq(z.game.teams->data[k].name, names[k]);
        cr_assert_not_null(z.game.teams->data[k].eggs);
        cr_assert_eq(z.game.teams->data[k].eggs->size, client_nb);
    }

    destroy_program(&z);
}

Test(program, badport)
{
    int client_nb = 10;
    int port = 1;
    int width = 10;
    int height = 10;
    int freq = 100;
    char *names[] = {"toto", "tata", NULL};
    size_t i = 0;

    zappy_t z;
    args_infos_t args = {
        .clients_nb = client_nb,
        .port = port,
        .width = width,
        .height = height,
        .freq = freq,
        .names = vec_create_vector_str_t(10),
    };

    for (; names[i]; i++) {
        vec_pushback_vector_str_t(args.names, str_snew(names[i]));
    }

    cr_assert_eq(init_program(&args, &z), ERROR);
}
