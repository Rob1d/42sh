/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** as variable
*/

#include "../includes/minishell.h"

static char *check_my_var(char *str, shell_t *sh, char **env)
{
    for (int i = 0; env[i] != NULL; ++i)
        if (str_start_with(env[i], str))
            return strdup(env[i]) + strlen(str) + 1;
    for (var_t *tmp = sh->lk_var; tmp != NULL; tmp = tmp->next)
        if (is_str_equal(str, tmp->name))
            return strdup(tmp->value);
    return NULL;
}

int len_double_tab(char **tab)
{
    int i = 0;
    for (; tab[i] != NULL; ++i);
    return i;
}

int get_total_len_double_tab(char **tab)
{
    int ret = 0;
    for (int i = 0; tab[i] != NULL; ++i)
        ret += strlen(tab[i]);
    return ret;
}

char *get_concat(char **pars)
{
    char *res = malloc(sizeof(char) * (get_total_len_double_tab(pars) * 2) + 1);
    res[0] = '\0';
    for (int i = 0; pars[i] != NULL; ++i) {
        strcat(res, pars[i]);
        strcat(res, " ");
    }
    return res;
}

char *as_var(char *command, shell_t *sh, char **env)
{
    char **pars = parsing(command);
    char *tmp_var = NULL;
    bool changed = false;
    for (int i = 0; pars[i] != NULL; ++i) {
        if (pars[i][0] == '$') {
            tmp_var = check_my_var(pars[i] + 1, sh, env);
            changed = true;
        }
        if (changed && tmp_var == NULL) {
            fprintf(stderr, "%s: Undefined variable.\n", pars[i] + 1);
            return NULL;
        }
        if (changed) {
            pars[i] = tmp_var;
            command = get_concat(pars);
            return as_var(command, sh, env);
        }
        changed = false;
    }
    return command;
}