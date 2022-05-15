/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** output
*/

#include "../../includes/minishell.h"

void special_output(shell_t *sh)
{
    sh->last_return == 0 ? printf("\033[0;32m") : printf("\033[0;31m");
    printf("✈  ");
    printf("\033[0;34m%s \033[0;35m~ ", sh->user_name);
    printf("\033[0m");
}