/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command
*/

#pragma once

enum ai_command_e {
    Forward,
    Right,
    Left,
};

typedef struct {
    enum ai_command_e command;
    void *args;
} command_t;
