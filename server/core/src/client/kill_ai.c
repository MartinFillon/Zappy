/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** kill_client
*/

#include <stdio.h>
#include <unistd.h>

#include "core/client.h"
#include "core/types/ai.h"
#include "utils.h"

static void erase_dead_ai(int id, struct vector_ai_t *ais)
{
    ai_t *ai = calloc(1, sizeof(ai_t));

    ai->id = id;
    vec_erase_vector_ai_t(ais, &ai, &cmp_ais);
    free(ai);
}

void kill_ai(struct client_list *clients, struct vector_ai_t *ais, size_t i)
{
    erase_dead_ai(clients->data[i]->ai->id, ais);
    close_client(clients->data[i], clients);
    vec_erase_at_client_list(clients, i);
}
