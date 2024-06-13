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
    vec_pushback_options(opts, (option_t){.identifier = "-p", .type = UINT});
    vec_pushback_options(opts, (option_t){.identifier = "-x", .type = UINT});
    vec_pushback_options(opts, (option_t){.identifier = "-y", .type = UINT});
    vec_pushback_options(opts, (option_t){.identifier = "-f", .type = UINT});
    struct args *ag = parse(av, ac, opts);

    for (size_t i = 0; i < ag->size; i++) {
        dprintf(2, "%s=", ag->data[i].option->identifier);
        switch (ag->data[i].option->type) {
            case INT:
                dprintf(2, "%d\n", ag->data[i].value.number);
                break;
            case STRING:
                dprintf(2, "%s\n", ag->data[i].value.string);
                break;
            case UINT:
                dprintf(2, "%u\n", ag->data[i].value.unsigned_number);
                break;
            case FLOAT:
                dprintf(2, "%f\n", ag->data[i].value.flt);
                break;
            case BOOL:
                dprintf(
                    2, "%s\n", ag->data[i].value.boolean ? "true" : "false"
                );
                break;
        }
    }
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
