/*
** EPITECH PROJECT, 2022
** builtin tools
** File description:
** tools for the builtins
*/

#include "../includes/minishell.h"

bool is_builtin(pipe_t *ppt, int nb)
{
    char **pars = parsing(ppt->commands[nb]);
    if (is_str_equal(ppt->commands[nb], "env"))
        close(ppt->return_last);
    if (is_str_equal(ppt->commands[nb], "exit"))
        exit(0);
    if (is_str_equal(pars[0], "cd")) {
        my_cd(pars, ppt->sh, ppt->env);
        return 1;
    }
    if (is_env(ppt->env, pars))
        return 1;
    return 0;
}

bool is_builtin_name(char *str)
{
    return (is_str_equal(str, "cd") || is_str_equal(str, "env") || is_str_equal
            (str, "setenv") || is_str_equal(str, "unsetenv")) ? true : false;
}
