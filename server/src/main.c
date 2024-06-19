/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "core/server.h"
#include "logger.h"
#include "macros.h"
#include "options/option.h"
#include "options/parser.h"
#include "args_info.h"
#include "options_def.h"

static void fill_infos(args_infos_t *infos, struct args *const ag)
{
    str_t *log_level = get_arg(ag, "-l").string;

    infos->clients_nb = get_arg(ag, "-c").unsigned_number;
    infos->port = get_arg(ag, "-p").unsigned_number;
    infos->width = get_arg(ag, "-x").unsigned_number;
    infos->height = get_arg(ag, "-y").unsigned_number;
    infos->freq = get_arg(ag, "-f").flt;
    infos->names = get_arg(ag, "-n").string_list;
    infos->level = set_log_level_from_str(log_level ? log_level->data : NULL);
    infos->displayer_path = get_arg(ag, "-d").string;
}

static struct options *create_opts(void)
{
    struct options *opts = vec_create_options(7);

    for (int i = 0; OPTIONS[i].identifier != NULL; i++) {
        vec_pushback_options(opts, OPTIONS[i]);
    }
    return opts;
}

static void destroy_args(struct args *ag, struct options *opts)
{
    if (ag != NULL)
        free_args(ag);
    vec_destroy_options(opts);
}

static int run_program(args_infos_t *args)
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    if (loop_server(args) == ERROR)
        return EPI_ERROR;
    return SUCCESS;
}

int main(int ac, char **av)
{
    args_infos_t args = {0};
    struct args *ag = NULL;
    struct options *opts = create_opts();

    srand(time(NULL));
    set_log_level(WARNING);
    if (!run_help(av, opts)) {
        ag = parse(av, ac, opts);
        if (ag == NULL) {
            logs(ERROR_LEVEL, "Error parsing arguments\n");
            return EPI_ERROR;
        }
        fill_infos(&args, ag);
        if (run_program(&args) == EPI_ERROR)
            return EPI_ERROR;
    }
    destroy_args(ag, opts);
    logs(INFO, "Server stopped\n");
    return SUCCESS;
}
