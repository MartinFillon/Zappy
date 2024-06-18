/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time
*/

#include "core/client.h"
#include "core/middlewares.h"
#include "core/router/route.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "logger.h"
#include "str.h"

void request_time(client_t *c, command_state_t *s)
{
    logs(DEBUG, "%.2f\n", s->game->frequency);
    prepare_response_cat(&c->io, "sgt %d\n", (int)s->game->frequency);
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
    prepare_response_cat(&c->io, "sst %d\n", nfreq);
    for (__auto_type i = 0ul; i < s->game->ais->size; i++) {
        update_clock(s->game->ais->data[i], nfreq);
    }
}
