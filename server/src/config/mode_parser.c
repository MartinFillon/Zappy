/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** mode_parser
*/

#include "types/client.h"

enum client_type_e get_mode(char const *restrict mode)
{
    if (strcmp(mode, "GRAPHIC") == 0)
        return GUI;
    if (strcmp(mode, "IA") == 0)
        return AI;
    return UNSET;
}
