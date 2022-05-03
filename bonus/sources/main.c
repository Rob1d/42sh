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

int main(int av, char **argc, char **env)
{
    char **new_env = env;
    cd *cd_params = malloc(sizeof(cd) + 1);
    params_cd(cd_params);
    path_to_home(cd_params->user);
    signal(SIGSEGV, segv);
    signal(SIGINT, sigint);
    while (!0)
        verify_command(new_env, cd_params);
    return 0;
}
