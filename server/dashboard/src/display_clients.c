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

static int display_ais(client_t *client, int x, int y)
{
    int pixls = 0;

    for (int i = 0; displayers[i] != NULL; i++) {
        pixls += displayers[i](client->ai, x, y + pixls);
    }
    return pixls;
}

static int display_client(client_t *client, int x, int y)
{
    if (client->type != AI)
        return 0;
    return display_ais(client, x, y);
}

void display_clients(struct client_list *lst, struct draw_state_s *st)
{
    int x = 20;
    int y = 20;
    int displayed = 0;

    for (int i = st->page; i < lst->size && i < st->page + st->paging; i++) {
        displayed = display_client(&lst->data[i], x, y);
        if (displayed != 0)
            DrawRectangleLines(x - 10, y - 5, 200, displayed + 10, WHITE);
        x += 200;
    }
}
