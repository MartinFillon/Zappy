/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** required
*/

#include "internal.h"
#include "logger.h"

bool check_required(struct options *opts, struct args *arguments)
{
    bool found = false;

    for (size_t i = 0; i < opts->size; i++) {
        if (!opts->data[i].required)
            continue;
        search_opt(&opts->data[i], arguments, &found);
        if (!found) {
            logs(
                ERROR_LEVEL,
                "Missing required option: %s\n",
                opts->data[i].identifier
            );
            return false;
        }
        found = false;
    }
    return true;
}
