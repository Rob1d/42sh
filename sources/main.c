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

static void change_base_values(shell_t *sh, char **env)
{
    char *new_term[] = {"setenv", "TERM", "42sh", NULL};
    set_env(env, new_term, sh);
}

int main(int av, char **argc, char **env)
{
    char **new_env = env;
    int pid = 0;
    int tmp;
    shell_t *sh = malloc(sizeof(shell_t));
    cd *cd_params = malloc(sizeof(cd) + 1);
    params_cd(cd_params);
    sh->cd_params = cd_params;
    sh->last_return = 0;
    sh->len_separator = 0;
    sh->separator_type = malloc(sizeof(int));
    path_to_home(sh->cd_params->user);
    change_base_values(sh, env);
    signal(SIGINT, sigint);
    pid = fork();
    if (pid == 0)
        while (!0)
            verify_command(new_env, sh);
    waitpid(pid, &tmp, 0);
    return 0;
}
