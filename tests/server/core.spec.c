/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** core.spec
*/

#include <criterion/criterion.h>

#include "core/gui/defs.h"
#include "core/router/route.h"
#include "core/types/client.h"
#include "zappy.h"
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
