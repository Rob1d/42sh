/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** output
*/

#include "../../includes/minishell.h"

void special_output(shell_t *sh)
{
    char *edit_pwd = strdup(sh->cd_params->new_PWD[2]);
    int i = strlen(edit_pwd);
    for (; edit_pwd[i] != '/'; --i);
    edit_pwd += i + 1;
    sh->last_return == 0 ? printf("\033[1;32m") : printf("\033[1;31m");
    printf("✈  ");
    printf("\033[1;34m%s {\033[1;36m%s\033[1;34m}\033[1;35m ~ ",
    sh->user_name, edit_pwd);
    printf("\033[0m");
    edit_pwd -= i + 1;
    free(edit_pwd);
}