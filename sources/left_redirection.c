/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** left redirection
*/

#include "../includes/minishell.h"

void no_acess(int file, char *n_file)
{
    bool check = false;
    for (int i = 0; n_file[i] != '\0'; ++i)
        check = n_file[i] != ' ' || n_file[i] != 9 ? true : check;
    if (!check) {
        my_put_str_er("Missing name for redirect.\n");
        exit(1);
    }
    if (file == -1) {
        my_put_str_er(n_file);
        !access(n_file, F_OK) ? my_put_str_er(": Permission denied.\n") :
        my_put_str_er(": No such file or directory.\n");
        exit(1);
    }
}

static void left_write(char *command, int i, char **env, shell_t *sh)
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
    no_acess(file, n_file);
    dup2(file, STDIN_FILENO);
    suppr_command(command, n_file, '<');
    process_commands(command, env, sh, false);
    close(file);
    exit(0);
}

int left_redirection(char *command, char **env, shell_t *sh)
{
    int i = 0;
    int pid = 0;
    for (; command[i] != '\0' && command[i] != '<'; ++i);
    if (command[i] == '\0')
        return 0;
    pid = fork();
    if (pid == 0)
        left_write(command, i, env, sh);
    waitpid(pid, NULL, 0);
    return 1;
}
