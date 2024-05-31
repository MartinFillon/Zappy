/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time
*/

#include "client.h"
#include "logger.h"
#include "middlewares.h"
#include "router/route.h"
#include "str.h"
#include "types/ai.h"
#include "types/client.h"

void request_time(client_t *c, command_state_t *s)
{
    prepare_response(&c->io, "sgt %d\n", s->game->frequency);
}

static void update_clock(ai_t *ai, double nfreq)
{
    ai->clock->frequency = nfreq;
    ai->food_clock->frequency = nfreq;
}

void update_time(client_t *c, command_state_t *s)
{
    int nfreq = 0;

    if (str_toint((long *)&nfreq, s->args->data[1]) || nfreq < 0)
        return send_invalid_args(c);
    s->game->frequency = nfreq;
    prepare_response(&c->io, "sst %d\n", nfreq);
    for (__auto_type i = 0ul; i < s->game->ais->size; i++) {
        update_clock(&s->game->ais->data[i], nfreq);
    }
}
