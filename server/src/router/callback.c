/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** callback
*/

#include "logger.h"
#include "router/callbacks.h"
#include "router/route.h"
#include "types/client.h"

callback_t get_callback(char const *name)
{
    for (int i = 0; CALLBACKS[i].name; i++) {
        if (strcmp(CALLBACKS[i].name, name) == 0)
            return CALLBACKS[i].f;
    }
    return NULL;
}

void placeholder(client_t *, command_state_t *s)
{
    logs(INFO, "Placeholder %d\n", s->args->size);
}
