/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy
*/

#include "core/types/ai.h"
#include "utils.h"

void destroy_ai(ai_t **ai)
{
    va_free(4, (*ai)->food_clock, (*ai)->clock, (*ai)->inventory, (*ai));
}
