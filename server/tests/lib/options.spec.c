/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** options.spec
*/

#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "options/converter.h"
#include "options/option.h"
#include "options/parser.h"

void redirect(void);

Test(options, convert_int)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"-42"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_int(&arg, &parser), false);
    cr_assert_eq(arg.value.number, -42);
}

Test(options, convert_int_fail)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"42a"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_int(&arg, &parser), true);
}

Test(options, convert_uint)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"42"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_uint(&arg, &parser), false);
    cr_assert_eq(arg.value.number, 42);
}

Test(options, convert_uint_fail)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"42a"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_uint(&arg, &parser), true);
}

Test(options, convert_float)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"42.42"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_float(&arg, &parser), false);
    cr_assert_eq(arg.value.flt, 42.42);
}

Test(options, convert_float_fail)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"42.42a"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_float(&arg, &parser), true);
}

Test(options, convert_bool)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"true"},
        .args_size = 0,
        .idx = 1,
    };

    cr_assert_eq(convert_bool(&arg, &parser), false);
    cr_assert_eq(arg.value.boolean, true);
    cr_assert_eq(parser.idx, 0);
}

Test(options, convert_string)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"hello"},
        .args_size = 0,
        .idx = 0,
    };

    cr_assert_eq(convert_string(&arg, &parser), false);
    cr_assert_str_eq(arg.value.string->data, "hello");
}

Test(options, convert_string_list)
{
    argument_t arg = {0};

    parser_t parser = {
        .options = NULL,
        .args = (char *[]){"hello", "world", "-p"},
        .args_size = 3,
        .idx = 0,
    };

    cr_assert_eq(convert_string_list(&arg, &parser), false);
    struct vector_str_t *lst = arg.value.string_list;
    cr_assert_eq(lst->size, 2);
    cr_assert_str_eq(lst->data[0]->data, "hello");
    cr_assert_str_eq(lst->data[1]->data, "world");
}

Test(options, check_required, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .required = true,
        .type = STRING,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    cr_assert_eq(check_required(opts, parsed), false);
    cr_assert_stderr_neq_str("");
}

Test(options, check_multiple_required, .init = redirect)
{
    option_t opt1 = {
        .identifier = "-f",
        .required = true,
        .type = STRING,
    };

    option_t opt2 = {
        .identifier = "-g",
        .required = false,
        .type = INT,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt1);
    vec_pushback_options(opts, opt2);

    struct args *parsed = vec_create_args(1);

    cr_assert_eq(check_required(opts, parsed), false);
    cr_assert_stderr_neq_str("");
}

Test(options, apply_defaults_str, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .default_value = {.string = "Str"},
        .has_default = true,
        .type = STRING,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 1);
    cr_assert_str_eq(parsed->data[0].value.string->data, "Str");
}

Test(options, apply_defaults_int, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .default_value = {.number = 42},
        .has_default = true,
        .type = INT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 1);
    cr_assert_eq(parsed->data[0].value.number, 42);
}

Test(options, apply_defaults_uint, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .default_value = {.unsigned_number = 42},
        .has_default = true,
        .type = UINT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 1);
    cr_assert_eq(parsed->data[0].value.unsigned_number, 42);
}

Test(options, apply_defaults_float, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .default_value = {.flt = 42.42},
        .has_default = true,
        .type = FLOAT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 1);
    cr_assert_eq(parsed->data[0].value.flt, 42.42);
}

Test(options, apply_defaults_bool, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .default_value = {.boolean = true},
        .has_default = true,
        .type = BOOL,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = vec_create_args(1);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 1);
    cr_assert_eq(parsed->data[0].value.boolean, true);
}

Test(options, apply_multiple_defaults, .init = redirect)
{
    option_t opt1 = {
        .identifier = "-f",
        .default_value = {.string = "Str"},
        .has_default = true,
        .type = STRING,
    };

    option_t opt2 = {
        .identifier = "-g",
        .default_value = {.number = 42},
        .has_default = true,
        .type = INT,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt1);
    vec_pushback_options(opts, opt2);

    struct args *parsed = vec_create_args(2);

    argument_t arg = {
        .option = &opt2,
        .value = {.number = 89},
    };

    vec_pushback_args(parsed, arg);

    set_defaults(opts, parsed);
    cr_assert_eq(parsed->size, 2);
    cr_assert_str_eq(parsed->data[1].value.string->data, "Str");
    cr_assert_eq(parsed->data[0].value.number, 89);
}

Test(options, full_parse, .init = redirect)
{
    option_t opt1 = {
        .identifier = "-f",
        .required = true,
        .type = STRING,
    };

    option_t opt2 = {
        .identifier = "-g",
        .default_value = {.number = 42},
        .has_default = true,
        .type = INT,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt1);
    vec_pushback_options(opts, opt2);

    struct args *parsed = parse((char *[]){"", "-f", "Str"}, 3, opts);

    cr_assert_eq(parsed->size, 2);
    cr_assert_str_eq(parsed->data[0].value.string->data, "Str");
    cr_assert_eq(parsed->data[1].value.number, 42);
}

Test(options, parse_unknown_type, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .required = true,
        .type = 42,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "Str"}, 3, opts);

    cr_assert_eq(parsed, NULL);
    cr_assert_stderr_neq_str("");
}

Test(options, parse_unknown_option, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .required = true,
        .type = STRING,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-g", "Str"}, 3, opts);

    cr_assert_eq(parsed, NULL);
    cr_assert_stderr_neq_str("");
}

Test(options, parse_missing_value, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .required = true,
        .type = STRING,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f"}, 2, opts);

    cr_assert_eq(parsed, NULL);
    cr_assert_stderr_neq_str("");
}

Test(options, parse_invalid_argument, .init = redirect)
{
    option_t opt = {
        .identifier = "-f",
        .required = true,
        .type = UINT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "-42a"}, 3, opts);

    cr_assert_eq(parsed, NULL);
    cr_assert_stderr_neq_str("");
}

Test(options, free_args)
{
    option_t opt1 = {
        .identifier = "-f",
        .type = STRING,
    };

    option_t opt2 = {
        .identifier = "-g",
        .type = STRING_LIST,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt1);
    vec_pushback_options(opts, opt2);

    struct args *parsed =
        parse((char *[]){"", "-f", "Str", "-g", "Str1", "Str2"}, 6, opts);

    free_args(parsed);
}

Test(options, help_message, .init = redirect)
{
    option_t opt = {
        .identifier = "-k",
        .type = BOOL,
        .description = "Kill the server",
    };

    option_t opt2 = {
        .identifier = "-z",
        .type = BOOL,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt);
    vec_pushback_options(opts, opt2);

    cr_assert_eq(run_help((char *[]){"./server", "-h", "other"}, opts), true);

    cr_assert_stdout_eq_str(
        "Usage:\n\t./server [options]\n\nOptions:\n\t-k:\tKill the "
        "server\n\t-z\n"
    );
}

Test(options, help_no_help)
{
    option_t opt = {
        .identifier = "-k",
        .type = BOOL,
        .description = "Kill the server",
    };

    option_t opt2 = {
        .identifier = "-z",
        .type = BOOL,
    };

    struct options *opts = vec_create_options(2);
    vec_pushback_options(opts, opt);
    vec_pushback_options(opts, opt2);

    cr_assert_eq(run_help((char *[]){"./server", "other"}, opts), false);
}

Test(options, get_string)
{
    option_t opt = {
        .identifier = "-f",
        .type = STRING,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "Str"}, 3, opts);

    cr_assert_str_eq(get_arg(parsed, "-f").string->data, "Str");
}

Test(options, get_int)
{
    option_t opt = {
        .identifier = "-f",
        .type = INT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "42"}, 3, opts);

    cr_assert_eq(get_arg(parsed, "-f").number, 42);
}

Test(options, get_uint)
{
    option_t opt = {
        .identifier = "-f",
        .type = UINT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "42"}, 3, opts);

    cr_assert_eq(get_arg(parsed, "-f").unsigned_number, 42);
}

Test(options, get_float)
{
    option_t opt = {
        .identifier = "-f",
        .type = FLOAT,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "42.42"}, 3, opts);

    cr_assert_eq(get_arg(parsed, "-f").flt, 42.42);
}

Test(options, get_bool)
{
    option_t opt = {
        .identifier = "-f",
        .type = BOOL,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f"}, 2, opts);

    cr_assert_eq(get_arg(parsed, "-f").boolean, true);
}

Test(options, get_string_list)
{
    option_t opt = {
        .identifier = "-f",
        .type = STRING_LIST,
    };

    struct options *opts = vec_create_options(1);
    vec_pushback_options(opts, opt);

    struct args *parsed = parse((char *[]){"", "-f", "Str1", "Str2"}, 4, opts);

    struct vector_str_t *lst = get_arg(parsed, "-f").string_list;

    cr_assert_eq(lst->size, 2);
    cr_assert_str_eq(lst->data[0]->data, "Str1");
    cr_assert_str_eq(lst->data[1]->data, "Str2");
}
