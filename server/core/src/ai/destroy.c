/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy
*/

#include "types/ai.h"
#include "utils.h"

void destroy_ai(ai_t *ai)
{
    va_free(2, ai->food_clock, ai->clock);
}
