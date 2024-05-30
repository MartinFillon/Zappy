/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time
*/

#include "client.h"
#include "types/client.h"
#include "utils.h"

void request_time(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    (void) clients;
    if (c->type != GUI)
        return;
    if (args[0] != '\0')
        return send_client(c, "sbp\n");
    send_client(c, "sgt %d\n", g->frequency);
}

void update_time(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    int nfreq = 0;

    (void) clients;
    if (c->type != GUI)
        return;
    if (parse_number(args, (long *)&nfreq) == false || nfreq < 0)
        return send_client(c, "sbp\n");
    g->frequency = nfreq;
    send_client(c, "sst %d\n", nfreq);
    for (__auto_type i = 0ul; i < g->ais->size; i++) {
        g->ais->data[i].clock->frequency = nfreq;
        g->ais->data[i].food_clock->frequency = nfreq;
    }
}
