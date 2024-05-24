/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time
*/

#include "client.h"
#include "types/client.h"
#include "utils.h"

void request_time(char *args, client_t *c, game_t *g)
{
    if (c->type != GUI)
        return;
    if (args[0] != '\0')
        return send_client(c, "sbp\n");
    send_client(c, "sgt %d\n", g->freq);
}

void update_time(char *args, client_t *c, game_t *g)
{
    int nfreq = 0;

    if (c->type != GUI)
        return;
    if (parse_number(args, (long *)&nfreq) == false || nfreq < 0)
        return send_client(c, "sbp\n");
    g->freq = nfreq;
    send_client(c, "sst %d\n", nfreq);
}
