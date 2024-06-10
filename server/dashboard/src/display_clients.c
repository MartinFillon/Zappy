/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_clients
*/

#include <raylib.h>
#include <stdio.h>
#include "core/types/client.h"
#include "core/types/object.h"
#include "zappy.h"

static void display_id(size_t id, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "AI %ld", id);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
}

static void display_team(char *team, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "Team: %s", team);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
}

static void display_object(const char *const name, size_t count, int x, int y)
{
    char *txt = NULL;

    asprintf(&txt, "%s %ld", name, count);
    DrawText(txt, x, y, 20, WHITE);
    free(txt);
}

static int display_ais(client_t *client, int x, int y)
{

    display_id(client->ai->id, x, y);
    y += 20;
    display_team(client->ai->team->name, x, y);
    y += 20;
    for (size_t i = 0; i < OBJ_COUNT; i++) {
        display_object(all_obj[i].name, client->ai->inventory[i], x, y);
        y += 20;
    }
    return y;
}

static int display_client(client_t *client, int x, int y)
{
    if (client->type != AI)
        return 0;
    return display_ais(client, x, y);
}

void display_clients(struct client_list *lst)
{
    int x = 10;
    int y = 10;

    for (size_t i = 0; i < lst->size; i++) {
        y += display_client(&lst->data[i], x, y);
    }
}
