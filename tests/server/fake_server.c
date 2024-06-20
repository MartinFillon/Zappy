/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** add_client
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <criterion/criterion.h>

#include "core/client.h"
#include "core/server.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/game.h"
#include "core/types/object.h"
#include "core/types/team.h"
#include "zappy.h"

client_t *new_fake_client(void)
{
    static int id = 0;

    char *address = NULL;
    asprintf(&address, "client_%d", id++);
    int fd = open(address, O_RDWR);
    cr_assert_neq(fd, -1);
    return init_client(fd, address, 0);
}

client_t *new_fake_ai_client(
    team_t *test_team,
    game_t *test_game,
    struct client_list *lst
)
{
    client_t *client = new_fake_client();

    client->type = AI;
    cr_assert(init_ai(test_game, client, test_team, lst));
    return client;
}

client_t *new_fake_gui_client(void)
{
    client_t *client = new_fake_client();

    client->type = GUI;
    return client;
}

void close_client_test(client_t *client, zappy_t *z, int i)
{
    remove(client->address);
    if (client->type != AI) {
        close_client(client, z->clients);
        vec_erase_at_client_list(z->clients, i);
    } else {
        kill_ai(z->clients, z->game.ais, i);
    }
}
