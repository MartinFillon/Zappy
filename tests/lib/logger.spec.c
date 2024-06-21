/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** logger.spec
*/

#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "logger/internal.h"
#define TEST 1
#include "logger.h"

void redirect(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(logger, test_logger_set_log_level)
{
    set_log_level(WARNING);
    struct logger_s *lg = get_mut_logger();
    cr_assert(lg->level == WARNING);
}

Test(logger, test_logger_set_log_level_from_str)
{
    set_log_level_from_str("WARNING");
    struct logger_s *lg = get_mut_logger();
    cr_assert(lg->level == WARNING);
}

Test(logger, test_logger_set_log_level_from_str_unkown)
{
    set_log_level_from_str("RATIO");
    struct logger_s *lg = get_mut_logger();
    cr_assert(lg->level == ERROR_LEVEL);
}

Test(logger, test_logger_set_log_level_from_str_null)
{
    set_log_level_from_str(NULL);
    struct logger_s *lg = get_mut_logger();
    cr_assert(lg->level == ERROR_LEVEL);
}

Test(logger, test_logger_print, .init = redirect)
{
    set_log_level(INFO);
    time_t t;
    time(&t);
    char buf[sizeof "2011-10-08T07:07:09Z"];

    strftime(buf, sizeof(buf), "%FT%TZ", gmtime(&t));
    logs(INFO, "test\n");
    char *expected = NULL;
    asprintf(&expected, "[%s INFO]: test\n", buf);
    cr_assert_stderr_eq_str(expected);
    free(expected);
}

Test(logger, test_logger_disable, .init = redirect)
{
    set_log_level(DISABLE);
    logs(DEBUG, "test\n");
    cr_assert_stderr_neq_str("test\n");
}
