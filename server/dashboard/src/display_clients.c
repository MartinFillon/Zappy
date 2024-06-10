/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_clients
*/

#include <raylib.h>
#include <stdio.h>
#include "core/types/client.h"
#include "zappy.h"

void display_client(client_t *client, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "fd: %d", client->fd);
    DrawText(txt, x, y, 20, WHITE);
}

void display_clients(struct client_list *lst)
{
    int x = 10;
    int y = 10;

    for (size_t i = 0; i < lst->size; i++) {
        display_client(&lst->data[i], x, y);
        y += 20;
    }
}
