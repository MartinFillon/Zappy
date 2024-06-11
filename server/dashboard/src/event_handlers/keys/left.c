/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left
*/

#include "dashboard/internal.h"

void handle_left_key_event(struct draw_state_s *st)
{
    if (st->page != 0)
        st->page -= st->paging;
}
