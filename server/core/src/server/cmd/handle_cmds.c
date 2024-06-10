/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_cmds
*/

#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "server.h"
#include "str.h"
#include "zappy.h"
#include "serv_cmd/serv_cmds.h"

static void run_serv_functions(
    zappy_t *z,
    const serv_cmds_t *cmd,
    struct vector_str_t *args
)
{
    if (args->size != cmd->nb_args + 1)
        return logs(ERROR_LEVEL, "Incorrect number of argument\n");
    cmd->func(z, args);
}

void handle_server_cmd(char const *cmd, zappy_t *z)
{
    str_t *str_cmd = str_snew(cmd);
    struct vector_str_t *args = NULL;

    if (!str_cmd)
        return logs(ERROR_LEVEL, "Allocation Error\n");
    args = str_split(str_cmd, " \t");
    str_free(str_cmd);
    if (!args)
        return logs(ERROR_LEVEL, "Allocation Error\n");
    for (size_t i = 0; SERV_CMDS[i].name != NULL; i++) {
        if (strcmp(SERV_CMDS[i].name, args->data[0]->data) == 0) {
            run_serv_functions(z, &SERV_CMDS[i], args);
            vec_free_vector_str_t(args, str_free);
            return;
        }
    }
    vec_free_vector_str_t(args, str_free);
}