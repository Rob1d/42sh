/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** main for the minishell1
*/

#include "../includes/minishell.h"

void segv(int sig)
{
    exit(0);
}

void sigint(int sig)
{
    write(1, "\nRob1 > ", 8);
    if (fork() == 0)
        exit(0);
}

static void flag_h(int av, char **argc)
{
    if (av == 2 && is_str_equal(argc[1], "-h")) {
        printf("42sh is a little linux shell\n-h for the help and quit\n"
        "-a for the advanced mode\n"
        "and nothing for the simplest (and fastest) mode\n");
        exit(0);
    }
}

int main(int av, char **argc, char **env)
{
    char **new_env = env;
    int pid = 0;
    int tmp;
    shell_t *sh = malloc(sizeof(shell_t));
    params_shell(av, argc, sh);
    flag_h(av, argc);
    signal(SIGINT, sigint);
    pid = fork();
    if (pid == 0)
        while (!0)
            verify_command(new_env, sh);
    waitpid(pid, &tmp, 0);
    free(sh->cd_params);
    free(sh);
    return 0;
}
