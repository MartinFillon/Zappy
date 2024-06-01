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

#include "logger.h"
#include "macros.h"
#include "server.h"
#include "utils.h"
#include "args_info.h"

static void sig(int signum)
{
    (void)signum;
}

int main(int ac, char const **av)
{
    args_infos_t args = {0};

    srand(time(NULL));
    if (ac == 2 && (!strcmp(av[1], "--help") || !strcmp(av[1], "-h"))) {
        display_help();
        return SUCCESS;
    }
    if (parse_command_line(av, &args) == false)
        return EPI_ERROR;
    signal(SIGINT, &sig);
    if (loop_server(&args) == ERROR)
        return EPI_ERROR;
    my_free_box(args.names);
    logs(INFO, "Server stopped\n");
    return SUCCESS;
}
