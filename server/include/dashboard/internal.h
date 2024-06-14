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
#define FONT_SIZE 20

struct draw_state_s {
    size_t width;
    size_t height;
    size_t fps;
    size_t page;
    size_t paging;
};

/**
 * @brief displays a text on screen when waiting for connections
 */
void wait_for_connections(void);

/**
 * @brief display all the clients info on screen
 *
 * @param lst all the clients
 * @param st the state of the window
 */
void display_clients(struct client_list *lst, struct draw_state_s *st);

/**
 * @brief handle all the events received by the window
 *
 * @param st the state of the window
 */
void poll_events(struct draw_state_s *st);

/**
 * @brief displays general infos such as the global ticks
 *
 * @param game all the game infos
 */
void display_general_infos(game_t *game);
