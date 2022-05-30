/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** pipe gestion
*/

#include "../includes/minishell.h"

static pipe_t *init_pipes(char *command, char **env, shell_t *sh)
{
    pipe_t *ppt;
    int len_pipes = 0;
    for (int i = 0; command[i] != '\0'; ++i)
        if (command[i] == '|')
            ++len_pipes;
    if (len_pipes == 0)
        return NULL;
    ppt = malloc(sizeof(pipe_t));
    ppt->len_pipe = len_pipes + 1;
    ppt->env = env;
    ppt->commands = split_commands(command);
    ppt->return_last = -1;
    ppt->sh = sh;
    return ppt;
}

static void first_pipe(pipe_t *ppt)
{
    int first_pid = 0;
    if (pipe(ppt->pipe_fd) == -1)
        exit(84);
    first_pid = fork();
    if (first_pid == 0) {
        dup2(ppt->pipe_fd[1], STDOUT_FILENO);
        process_commands(ppt->commands[0], ppt->env, ppt->sh, false);
        exit(0);
    }
    ppt->return_last = ppt->pipe_fd[0];
    close(ppt->pipe_fd[1]);
}

static void middle_pipe(pipe_t *ppt, int nb)
{
    int pid = 0;
    int rd = 0;
    if (pipe(ppt->pipe_fd) == -1)
        exit(84);
    pid = fork();
    if (pid == 0) {
        dup2(ppt->return_last, STDIN_FILENO);
        dup2(ppt->pipe_fd[1], STDOUT_FILENO);
        process_commands(ppt->commands[nb], ppt->env, ppt->sh, false);
        exit(0);
    }
    close(ppt->pipe_fd[1]);
    ppt->return_last = ppt->pipe_fd[0];
    verify_return(rd);
}

static int end_pipe(pipe_t *ppt, int nb)
{
    int pid = 0;
    int rd = 0;
    if (is_builtin(ppt, nb)) {
        close(ppt->return_last);
        return 1;
    }
    pid = fork();
    if (pid == 0) {
        dup2(ppt->return_last, STDIN_FILENO);
        close(ppt->return_last);
        process_commands(ppt->commands[nb], ppt->env, ppt->sh, false);
        exit(0);
    }
    close(ppt->return_last);
    waitpid(pid, &rd, 0);
    verify_return(rd);
    return 0;
}

int pipe_gestion(char *command, char **env, shell_t *sh)
{
    pipe_t *ppt = init_pipes(command, env, sh);
    int i = 1;
    int pid = 0;
    bool good = false;
    if (ppt == NULL)
        return 0;
    for (int j = str_len(command) - 1; command[j] != '|'; --j)
        good = (command[j] != ' ' && command[j] != 9 ) ? true : good;
    if (!good) {
        my_put_str_er("Invalid null command.\n");
        return 1;
    }
    first_pipe(ppt);
    for (; i < ppt->len_pipe - 1; ++i)
        middle_pipe(ppt, i);
    end_pipe(ppt, i);
    return 1;
}
