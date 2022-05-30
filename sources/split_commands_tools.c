/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** split
*/

#include "../includes/minishell.h"

static void move_letters(char **parsed, int i)
{
    for (int j = 1; parsed[i][j - 1] != '\0'; ++j)
        parsed[i][j - 1] = parsed[i][j];
}

void check_spaces(char **parsed)
{
    for (int i = 0; parsed[i] != NULL; i++) {
        if (parsed[i][str_len(parsed[i]) - 1] == ' ')
            parsed[i][str_len(parsed[i]) - 1] = '\0';
        if (parsed[i][0] == ' ')
            move_letters(parsed, i);
    }
}

void check_execution(char **parsing_command, pipe_t *ppt)
{
    if (!access(put_bin(parsing_command[0]), X_OK))
        execve(put_bin(parsing_command[0]), parsing_command, ppt->env);
    else if (!access(parsing_command[0], F_OK))
        execve(parsing_command[0], parsing_command, ppt->env);
    else
        error_acess(parsing_command[0]);
    if (errno == ENOEXEC)
        my_put_str_er("Exec format error. Wrong Architecture.\n");
}
