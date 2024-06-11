/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right
*/

#include "dashboard/internal.h"

void handle_right_key_event(struct draw_state_s *st)
{
    st->page += st->paging;
}
