/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** internal
*/

#pragma once

#include <stddef.h>
#include "zappy.h"

struct draw_state_s {
    size_t width;
    size_t height;
    size_t fps;
    size_t page;
};

void wait_for_connections(void);
void display_clients(struct client_list *lst, size_t start, size_t end);
