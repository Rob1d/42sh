/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** gestion of the env
*/

#include "../includes/minishell.h"

char *set_value(char **pars)
{
    int len = str_len(pars[1]) + str_len(pars[2]);
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
    for (int i = 0; pars[2][i] != '\0'; ++i) {
        if (pars[2][i] != 34 && pars[2][i] != 39) {
            value[cp] = pars[2][i];
            ++cp;
        }
    }
    value[cp] = '\0';
    return value;
}

void augment_size(char **env)
{
    char **new_env = malloc(sizeof(char *) * (len_env(env) + 3));
    int i = 0;
    for (; env[i] != NULL; ++i)
        new_env[i] = env[i];
    new_env[i + 1] = NULL;
    env = new_env;
}

int set_env(char **env, char **pars)
{
    int env_len = len_env(env);
    if (len_env(pars) == 1) {
        my_show_word_array(env);
        return 1;
    }
    if (!error_setenv(pars))
        return 84;
    augment_size(env);
    if (len_env(pars) == 2)
        env[search_in_env(env, pars[1])] = set_value_two(pars);
    if (len_env(pars) == 3)
        env[search_in_env(env, pars[1])] = set_value(pars);
    env[env_len + 1] = NULL;
    return 0;
}
