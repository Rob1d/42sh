/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** left redirection
*/

#include "../includes/minishell.h"

static void left_write(char *command, int i, char **env, cd *cd_params)
{
    int file = 0;
    int check = 0;
    char *n_file;
    for (; command[i] == '<'; ++i)
        ++check;
    n_file = name_file(command, i);
    if (check == 1)
        file = open(n_file, O_RDONLY);
    else
        file = open(n_file, O_RDONLY);
    if (file == -1) {
        my_put_str_er(n_file);
        my_put_str_er(": Permission denied.\n");
        exit(1);
    }
    dup2(file, STDIN_FILENO);
    suppr_command(command, n_file, '<');
    process_commands(command, env, cd_params, false);
    close(file);
    exit(0);
}

int left_redirection(char *command, char **env, cd *cd_params)
{
    int i = 0;
    int pid = 0;
    for (; command[i] != '\0' && command[i] != '<'; ++i);
    if (command[i] == '\0')
        return 0;
    pid = fork();
    if (pid == 0)
        left_write(command, i, env, cd_params);
    waitpid(pid, NULL, 0);
    return 1;
}