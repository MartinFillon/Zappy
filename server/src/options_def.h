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
};

static const option_t PORT = {
    .identifier = "-p",
    .type = UINT,
    .has_default = true,
    .default_value =
        {
            .unsigned_number = 8080,
        },
};

static const option_t WIDTH = {
    .identifier = "-x",
    .type = UINT,
    .has_default = true,
    .default_value =
        {
            .unsigned_number = 10,
        },
};

static const option_t HEIGHT = {
    .identifier = "-y",
    .type = UINT,
    .has_default = true,
    .default_value =
        {
            .unsigned_number = 10,
        },
};

static const option_t FREQUENCY = {
    .identifier = "-f",
    .type = UINT,
    .has_default = true,
    .default_value =
        {
            .unsigned_number = 100,
        },
};

static const option_t CLIENT_NUMBER = {
    .identifier = "-c",
    .type = UINT,
    .has_default = true,
    .default_value =
        {
            .unsigned_number = 10,
        },
};

static const option_t TEAM_NAMES = {
    .identifier = "-n",
    .type = STRING_LIST,
    .required = true,
};

static const option_t OPTIONS[] = {
    LOGGER_MODE,
    PORT,
    WIDTH,
    HEIGHT,
    FREQUENCY,
    CLIENT_NUMBER,
    TEAM_NAMES,
    {
        .identifier = NULL,
        .type = STRING,
    },
};
