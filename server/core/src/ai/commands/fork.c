/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_fork
*/

#include "core/client.h"
#include "core/router/route.h"
#include "core/types/client.h"
#include "core/types/team.h"
#include "logger.h"

static void send_and_log(client_t *cli, egg_t *egg, struct client_list *s)
{
    prepare_response_cat(&cli->io, "ok\n");
    broadcast_to(GUI, s, "pfk %d\n", cli->ai->id);
    broadcast_to(
        GUI,
        s,
        "enw %d %d %d %d\n",
        egg->id,
        cli->ai->id,
        egg->pos.x,
        egg->pos.y
    );
    logs(
        INFO,
        "Team %s has a new egg [%d]\n",
        cli->ai->team->name,
        cli->ai->team->eggs->size
    );
}

void handle_fork(client_t *cli, command_state_t *s)
{
    egg_t *egg = create_egg(cli->ai->pos.x, cli->ai->pos.y);

    if (!egg) {
        logs(ERROR_LEVEL, "Allocation error on fork handling");
        return;
    }
    logs(DEBUG, "Client %d AI %d is forking\n", cli->fd, cli->ai->id);
    queue_pushback_queue_egg_t(cli->ai->team->eggs, egg);
    return send_and_log(cli, egg, s->clients);
}
