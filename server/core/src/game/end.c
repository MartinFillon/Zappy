/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** end
*/

#include "core/client.h"
#include "zappy.h"

bool check_end(struct client_list *list)
{
    static bool winned = false;

    for (size_t i = 0; !winned && i < list->size; i++)
        if (list->data[i]->type == AI && list->data[i]->ai->level >= 8) {
            broadcast_to(GUI, list, "seg %s\n", list->data[i]->ai->team->name);
            winned = true;
            return true;
        }
    return false;
}
