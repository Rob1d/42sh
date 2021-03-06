/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** right redirection
*/

#include "../includes/minishell.h"

char *name_file(char *command, int i)
{
    char *n_file = malloc(strlen(command) - i + 1);
    int j = 0;
    for (; command[i] == ' '; ++i);
    for (; command[i + j] != '\0'; ++j) {
        if (command[i + j] != ' ')
            n_file[j] = command[i + j];
        else {
            ++i;
            --j;
        }
    }
    n_file[j] = '\0';
    return n_file;
}

void suppr_command(char *command, char *launched, char c)
{
    int i = 0;
    for (; command[i] != '\0' && command[i] != c; ++i);
    for (; command[i] != launched[0] && command[i] != '\0'; ++i)
        command[i] = ' ';
    for (int j = 0; command[i + j] == launched
    [j] && command[i + j] != '\0'; ++j)
        command[i + j] = ' ';
}

static int open_fd(int check, char *n_file)
{
    int file = 0;
    if (check == 1)
        file = open(n_file, O_CREAT | O_WRONLY, 0664);
    else
        file = open(n_file, O_CREAT | O_WRONLY | O_APPEND, 0664);
    no_acess(file, n_file);
    return file;
}

static void right_write(char *command, int i, char **env, shell_t *sh)
{
    int file = 0;
    int check = 0;
    char *n_file;
    for (; command[i] == '>'; ++i)
        ++check;
    n_file = name_file(command, i);
    file = open_fd(check, n_file);
    dup2(file, STDOUT_FILENO);
    suppr_command(command, n_file, '>');
    process_commands(command, env, sh, false);
    close(file);
    exit(0);
}

int right_redirection(char *command, char **env, shell_t *sh)
{
    int i = 0;
    int pid = 0;
    for (; command[i] != '\0' && command[i] != '>'; ++i);
    if (command[i] == '\0')
        return 0;
    pid = fork();
    if (pid == 0)
        right_write(command, i, env, sh);
    waitpid(pid, NULL, 0);
    return 1;
}
