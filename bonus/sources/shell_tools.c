/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** tools for the minshell
*/

#include "../includes/minishell.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_show_word_array(char **tab)
{
    int i = 0;
    int j = 0;
    while (tab[i] != NULL) {
        while (tab[i][j] != '\0') {
            my_putchar(tab[i][j]);
            ++j;
        }
        my_putchar('\n');
        j = 0;
        ++i;
    }
}

int move_env(char **env, int i)
{
    for (; env[i] != NULL; ++i)
        env[i] = env[i + 1];
    return 0;
}

int len_env(char **env)
{
    int i = 0;
    for (; env[i] != NULL; ++i);
    return i;
}

int is_env(char **env, char **pars)
{
    if (is_str_equal(pars[0], "env")) {
        my_show_word_array(env);
        return 1;
    }
    if (is_str_equal(pars[0], "setenv")) {
        set_env(env, pars);
        return 1;
    }
    if (is_str_equal(pars[0], "unsetenv")) {
        unset_loop(env, pars);
        return 1;
    }
    return 0;
}
