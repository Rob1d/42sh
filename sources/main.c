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
    int pid = 0;
    int tmp;
    shell_t *sh = malloc(sizeof(shell_t));
    cd *cd_params = malloc(sizeof(cd) + 1);
    params_cd(cd_params);
    sh->all_mode = (av == 2 && is_str_equal(argc[1], "-a")) ? true : false;
    sh->cd_params = cd_params;
    sh->last_return = 0;
    sh->len_separator = 0;
    sh->separator_type = malloc(sizeof(int));
    path_to_home(sh->cd_params->user);
    sh->user_name = strdup(sh->cd_params->user);
    ++sh->user_name;
    for (; *sh->user_name != '/'; ++sh->user_name);
    ++sh->user_name;
    signal(SIGINT, sigint);
    pid = fork();
    if (pid == 0)
        while (!0)
            verify_command(new_env, sh);
    waitpid(pid, &tmp, 0);
    return 0;
}
