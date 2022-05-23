/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** check the if statement
*/

#include "../includes/minishell.h"

static char *get_name_if(char *command, int *i)
{
    char *name = malloc(sizeof(char) * strlen(command) + 1 - *i);
    int j = 0;
    for (; command[*i] != ' ' && command[*i] != '\0'
    && command[*i] != '(' && command[*i] != ')'; ++*i, ++j)
        name[j] = command[*i];
    name[j] = '\0';
    return name;
}

static bool choose_equality(if_params_t *ipt)
{
    if (is_str_equal(ipt->equality_type, "==") &&
    is_str_equal(ipt->params[0], ipt->params[1]))
        return true;
    if (is_str_equal(ipt->equality_type, "!=") &&
    !is_str_equal(ipt->params[0], ipt->params[1]))
        return true;
    return false;
}

static bool get_statement(if_params_t *ipt, char **env, shell_t *sh)
{
    if (ipt->params[0][0] == '"') {
        ipt->params[0]++;ipt->params[0][strlen(ipt->params[0]) - 1] = '\0';
    }
    if (ipt->params[1][0] == '"') {
        ipt->params[1]++;ipt->params[1][strlen(ipt->params[1]) - 1] = '\0';
    }
    if (ipt->params[0][0] == '$') {
        ++ipt->params[0];
        for (int i = 0; env[i] != NULL; ++i)
            ipt->params[0] = str_star_with(env[i], ipt->params[0]) ? strdup(env[i]) : ipt->params[0];
        for (; *ipt->params[0] != '=' && *ipt->params[0] != '\0'; ++ipt->params[0]);
        *ipt->params[0] != '\0' ? ++ipt->params[0] : 0;
    }
    if (ipt->params[1][0] == '$') {
        ++ipt->params[1];
        for (int i = 0; env[i] != NULL; ++i)
            ipt->params[1] = str_star_with(env[i], ipt->params[1]) ? strdup(env[i]) : ipt->params[1];
        for (; *ipt->params[1] != '=' && *ipt->params[1] != '\0'; ++ipt->params[1]);
        *ipt->params[1] != '\0' ? ++ipt->params[1] : 0;
    }
    return choose_equality(ipt);
}

int if_statement(char *command, char **env, shell_t *sh)
{
    if_params_t ipt = {NULL, NULL, NULL, true};
    int i = 2;
    int j = 0;
    if (command[0] == 'i' && command[1] == 'f') {
        for (; command[i] == ' ' || command[i] == '('; ++i);
        ipt.params[0] = get_name_if(command, &i);
        for (; command[i] == ' '; ++i);
        ipt.equality_type = get_name_if(command, &i);
        for (; command[i] == ' '; ++i);
        ipt.params[1] = get_name_if(command, &i);
        ipt.res = get_statement(&ipt, env, sh);
        if (ipt.res) {
            for (j = strlen(command); j >= 0 && command[j] != ')'; --j);
            ++j;
            return j;
        }
        return strlen(command);
    }
    return 0;
}