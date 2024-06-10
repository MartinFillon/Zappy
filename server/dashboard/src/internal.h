/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** internal
*/

#pragma once

#include <stddef.h>
#include "core/types/client.h"

struct draw_state_s {
    size_t width;
    size_t height;
    size_t fps;
};

void wait_for_connections(void);
void display_clients(struct client_list *lst);
