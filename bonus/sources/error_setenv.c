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

int is_letter(char c)
{
    int a;
    a = ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') && c != '_') ? 1 : 0;
    return a;
}

int error_setenv(char **pars)
{
    if (len_env(pars) != 3 && len_env(pars) != 2) {
        my_put_str_er("setenv : Too many arguments.\n");
        return 0;
    }
    if (!is_letter(pars[1][0])) {
        my_put_str_er("setenv: Variable name must begin with a letter.\n");
        return 0;
    }
    for (int i = 0; pars[1][i] != '\0'; ++i)
        if (!is_letter(pars[1][i])) {
            my_put_str_er("setenv: Variable name");
            my_put_str_er(" must contain alphanumeric characters.\n");
            return 0;
        }
    return 1;
}
