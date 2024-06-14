/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** freeze_ais
*/

#include "core/types/ai.h"
#include "utils.h"

void freeze_ai(ai_t *ai, int id)
{
    ai->incant.is_incant = true;
    ai->incant.id_incant = id;
}

void unfreeze_ai(ai_t *ai)
{
    ai->incant.is_incant = false;
    ai->incant.id_incant = 0;
}
