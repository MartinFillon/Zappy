/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** internal
*/

#pragma once

#include <stddef.h>
#include "zappy.h"

#define FPS 60
#define WIDTH 800
#define HEIGHT 600
#define PAGING 4

struct draw_state_s {
    size_t width;
    size_t height;
    size_t fps;
    size_t page;
    size_t paging;
};

void wait_for_connections(void);
void display_clients(struct client_list *lst, struct draw_state_s *st);
