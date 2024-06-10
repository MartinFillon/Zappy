/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** kill_client
*/

#include <unistd.h>

#include "client.h"
#include "utils.h"

static void erase_dead_ai(int id, struct vector_ai_t *ais)
{
    ai_t ai = {0};

    ai.id = id;
    vec_erase_vector_ai_t(ais, ai, &cmp_ais);
}

void kill_ai(
    struct client_list *clients,
    struct vector_ai_t *ais,
    size_t i
)
{
    erase_dead_ai(clients->data[i].ai->id, ais);
    close_client(&clients->data[i], clients);
    vec_erase_at_client_list(clients, i);
}
