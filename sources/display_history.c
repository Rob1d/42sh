/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** dsiplay the history
*/

#include "../includes/minishell.h"

char **my_db_copy(char *db[])
{
    int i = 0;
    char **ret;
    for (;db[i] != NULL; ++i);
    ret = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; db[j] != NULL; ++j)
        ret[j] = db[j];
    ret[i] = NULL;
    return ret;
}

bool display_history(char *command, shell_t *sh)
{
    char **history;
    if (!is_str_equal(command, "history") && !is_str_equal(command, "!!"))
        return false;
    history = received_input(sh, false);
    sh->last_return = 0;
    for (int i = 0; history[i] != NULL; i++) {
        printf("%d\t%s\n", i, history[i]);
        free(history[i]);
    }
    free(history);
    return true;
}