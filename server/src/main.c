/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "core/server.h"
#include "logger.h"
#include "macros.h"
#include "options/option.h"
#include "options/parser.h"
#include "utils.h"
#include "args_info.h"

static void sig(int signum)
{
    (void)signum;
}

int main(int ac, char **av)
{
    set_log_level(DEBUG);
    struct options *opts = vec_create_options(1);

    vec_pushback_options(opts, (option_t){.identifier = "-l", .type = STRING});

    parse(av, ac, opts);
    // args_infos_t args = {0};

    // srand(time(NULL));
    // if (ac == 2 && (!strcmp(av[1], "--help") || !strcmp(av[1], "-h"))) {
    //     display_help();
    //     return SUCCESS;
    // }
    // if (parse_command_line(av, &args) == false)
    //     return EPI_ERROR;
    // signal(SIGINT, &sig);
    // if (loop_server(&args) == ERROR)
    //     return EPI_ERROR;
    // my_free_box(args.names);
    // logs(INFO, "Server stopped\n");
    return SUCCESS;
}
