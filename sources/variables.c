/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set variables
*/

#include "../includes/minishell.h"

int len_double_tab(char **tab)
{
    int i = 0;
    for (; tab[i] != NULL; ++i);
    return i;
}

static void add_variable(char *name, char *value, shell_t *sh)
{
    var_t *tmp = sh->lk_var;
    if (tmp == NULL) {
        sh->lk_var = malloc(sizeof(var_t));
        sh->lk_var->value = value;
        sh->lk_var->name = name;
        sh->lk_var->next = NULL;
        return;
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = malloc(sizeof(var_t));
    tmp->next->name = name;
    tmp->next->value = value;
    tmp->next->next = NULL;
}

void add_first_var(shell_t *sh)
{
    add_variable("user", sh->user_name, sh);
    add_variable("cwd", sh->cd_params->old_cd, sh);
    add_variable("one", "one", sh);
}

static void put_variables(char **pars, shell_t *sh, int j)
{
    char *value;
    int i = 0;
    char *var_name;
    var_name = strdup(pars[j]);
    for (; var_name[i] != '\0' && var_name[i] != '='; ++i);
    if (var_name[i] == '\0' || (var_name[i] == '=' && var_name[i + 1] == '\0'))
        value = NULL;
    else
        value = strdup(pars[j]) + i + 1;
    var_name[i] = '\0';
    add_variable(var_name, value, sh);
}

bool set_variable(char **pars, shell_t *sh)
{
    if (!is_str_equal("set", pars[0])) return false;
    if (pars[1] == NULL) {
        for (var_t *tmp = sh->lk_var; tmp != NULL; tmp = tmp->next) {
            printf("%s", tmp->name);
            tmp->value != NULL ? printf("\t%s", tmp->value) : 0;
            printf("\n");
        }
        return true;
    }
    for (int j = 1; pars[j] != NULL; ++j)
        put_variables(pars, sh, j);
    return true;
}