/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** options_def
*/

#pragma once

#include "options/option.h"

static const option_t LOGGER_MODE = {
    .identifier = "-l",
    .type = STRING,
    .description = "Set logger mode (ERROR, WARNING, INFO, DEBUG, DISABLE)",
    .has_default = true,
    .default_value = {.string = "WARNING"},
};

static const option_t PORT = {
    .identifier = "-p",
    .type = UINT,
    .has_default = true,
    .default_value = {.unsigned_number = 8080},
    .description = "Set the port to listen on",
};

static const option_t WIDTH = {
    .identifier = "-x",
    .type = UINT,
    .has_default = true,
    .default_value = {.unsigned_number = 10},
    .description = "Set the width of the map",
};

static const option_t HEIGHT = {
    .identifier = "-y",
    .type = UINT,
    .has_default = true,
    .default_value = {.unsigned_number = 10},
    .description = "Set the height of the map",
};

static const option_t FREQUENCY = {
    .identifier = "-f",
    .type = UINT,
    .has_default = true,
    .default_value = {.unsigned_number = 100},
    .description = "Set the frequency of the game",
};

static const option_t CLIENT_NUMBER = {
    .identifier = "-c",
    .type = UINT,
    .has_default = true,
    .default_value = {.unsigned_number = 10},
    .description = "Set the number of clients per team",
};

static const option_t TEAM_NAMES = {
    .identifier = "-n",
    .type = STRING_LIST,
    .required = true,
    .description = "Set the names of the teams",
};

static const option_t DISPLAYER = {
    .identifier = "-d",
    .type = STRING,
    .has_default = true,
    .default_value = {.string = "server/base.so"},
    .description = "Set the path to the displayer if you want to use one",
};

static const option_t OPTIONS[] = {
    LOGGER_MODE,
    PORT,
    WIDTH,
    HEIGHT,
    FREQUENCY,
    CLIENT_NUMBER,
    TEAM_NAMES,
    DISPLAYER,
    {
        .identifier = NULL,
        .type = STRING,
    },
};
