/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_clients
*/

#include <raylib.h>
#include <stdio.h>
#include "core/types/client.h"
#include "dashboard/displayers.h"
#include "dashboard/internal.h"

static void display_ais(client_t *client, int x, int y)
{
    for (size_t i = 0; displayers[i] != NULL; i++) {
        displayers[i](client->ai, x, y);
        y += 20;
    }
}

static void display_client(client_t *client, int x, int y)
{
    if (client->type != AI)
        return;
    display_ais(client, x, y);
}

void display_clients(struct client_list *lst, size_t start, size_t end)
{
    int x = 10;
    int y = 10;

    for (size_t i = start; i < lst->size && i < end; i++) {
        display_client(&lst->data[i], x, y);
        x += 200;
    }
}
