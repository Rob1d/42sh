/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** verify command
*/

#include "../includes/minishell.h"

static void verify_command_red(char **line, shell_t *sh)
{
    free(line);
    sh->len_separator = 0;
    free(sh->separator_type);
    sh->separator_type = malloc(sizeof(int));
}

bool is_empty_command(char const *command)
{
    for (int i = 0; command[i] != '\0'; ++i)
        if (command[i] != ' ' && command[i] != '\t')
            return false;
    return true;
}

void check_len_command(char **line, shell_t *sh)
{
    int cp = 0;
    for (int i = 0; line[i] != NULL; ++i)
        !is_empty_command(line[i]) || sh->separator_type[i] == 0 ? ++cp : 0;
    if (sh->len_separator >= cp) {
        sh->len_separator = -1;
        fprintf(stderr, "Invalid null command.\n");
        sh->last_return = 1;
    }
}

void verify_command(char **env, shell_t *sh)
{
    char **line = wait_commands(sh, env);
    int tmp = 0;
    bool last_return = true;check_len_command(line, sh);
    for (int i = 0; i <= sh->len_separator; ++i) {
        last_return = sh->len_separator > 0 && (sh->separator_type[i - 1] == 2
        && !last_return) ? false : true;
        tmp = if_statement(line[i], env, sh);
        if (((i == 0 || sh->separator_type[i - 1] == 0 ||
        (sh->separator_type[i - 1] == 1 && sh->last_return != 0) ||
        (sh->separator_type[i - 1] == 2 && sh->last_return == 0)))
        && last_return) {
            line[i] += tmp;
            line[i] = line[i][0] == '\0' ? strdup("ui") : line[i];
            process_commands(line[i], env, sh, false);
            line[i] -= is_str_equal(line[i], "ui") ? 0 : tmp;last_return = 1;
        } else
            last_return = false;
        free(line[i]);
    }
    verify_command_red(line, sh);
}
