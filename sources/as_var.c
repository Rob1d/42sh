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
    for (int i = 0; pars[i] != NULL; ++i)
        strcat(res, pars[i]);
    return res;
}

char **pars_var(char *command)
{
    char **ret = malloc(sizeof(char *) * 2);
    int cp = 0;
    int cp_i = 0;
    ret[0] = malloc(sizeof(char) * strlen(command) + 1);
    for (int i = 0; command[i] != '\0'; ++i) {
        if (command[i] == '$') {
            ret[cp][cp_i] = '\0';
            ++cp;
            ret = realloc(ret, sizeof(char * ) * (cp + 2));
            cp_i = 0;
            ret[cp] = malloc(sizeof(char) * (strlen(command) + 1));
        }
        ret[cp][cp_i] = command[i];
        ++cp_i;
    }
    ret[cp][cp_i] = '\0';
    ++cp;
    ret[cp] = NULL;
    return ret;
}

char *as_var(char *command, shell_t *sh, char **env)
{
    char **pars = pars_var(command);
    char *tmp_var = NULL;
    bool changed = false;
    for (int i = 0; pars[i] != NULL; ++i) {
        if (pars[i][0] == '$') {
            tmp_var = check_my_var(pars[i] + 1, sh, env);
            changed = true;
        }
        if (changed && tmp_var == NULL) {
            fprintf(stderr, "%s: Undefined variable.\n", pars[i] + 1);
            sh->last_return = 1;return NULL;
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
