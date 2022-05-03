/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** unsetenv
*/

#include "../includes/minishell.h"

int unset_loop(char **env, char **pars)
{
    for (int i = 1; pars[i] != NULL; ++i)
        unset_env(env, pars[i]);
    return 0;
}

int unset_env(char **env, char *to_reset)
{
    int i = 0;
    int j = 0;
    char *tmp = malloc(sizeof(char) * 1000000);
    while (env[i] != NULL) {
        for (j = 0; env[i][j] != '\0' && env[i][j] != '='; ++j)
            tmp[j] = env[i][j];
        tmp[j] = '\0';
        if (is_str_equal(tmp, to_reset))
            return move_env(env, i);
        ++i;
    }
    return 1;
}

int is_already(char *env, char *set)
{
    int j = 0;
    for (; env[j] != '=' && env[j] != '\0' && set[j] != '\0'; ++j)
        if (env[j] != set[j])
            return 0;
    if (set[j] == '\0' && env[j] != '=')
        return 0;
    return 1;
}

int search_in_env(char **env, char *set)
{
    int i = 0;
    for (; env[i] != NULL; ++i)
        if (is_already(env[i], set))
            return i;
    return i;
}
