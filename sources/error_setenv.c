/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** error handling for the setenv
*/

#include "../includes/minishell.h"

char *set_value_two(char **pars)
{
    int len = str_len(pars[1]);
    char *value = malloc(sizeof(char) * (len + 2));
    int cp = 0;
    for (int i = 0; pars[1][i] != '\0'; ++i) {
        if (pars[1][i] != 34 && pars[1][i] != 39) {
            value[cp] = pars[1][i];
            ++cp;
        }
    }
    value[cp] = '=';
    ++cp;
    value[cp] = '\0';
    return value;
}

int error_setenv(char **pars, shell_t *sh)
{
    if (len_env(pars) != 3 && len_env(pars) != 2) {
        my_put_str_er("setenv : Too many arguments.\n");
        sh->last_return = 1;
        return 0;
    }
    if (!IS_LETTER(pars[1][0])) {
        my_put_str_er("setenv: Variable name must begin with a letter.\n");
        sh->last_return = 1;
        return 0;
    }
    for (int i = 0; pars[1][i] != '\0'; ++i)
        if (!IS_LETTER(pars[1][i])) {
            my_put_str_er("setenv: Variable name");
            my_put_str_er(" must contain alphanumeric characters.\n");
            sh->last_return = 1;
            return 0;
        }
    return 1;
}
