/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** tools for the cd
*/

#include "../includes/minishell.h"

int path_to_home(char *cwd)
{
    int cp_slash = 0;
    for (int i = 0; cwd[i] != '\0'; ++i) {
        if (cwd[i] == '/')
            ++cp_slash;
        if (cp_slash == 3) {
            cwd[i] = '\0';
            return 1;
        }
    }
    return 0;
}

void apply_old(char *old_cd, char *tmp_buf)
{
    int i = 0;
    for (; old_cd[i] != '\0'; ++i)
        tmp_buf[i] = old_cd[i];
    tmp_buf[i] = '\0';
}

int minus_cd(shell_t *sh, char **env)
{
    char *tmp = malloc(sizeof(char) * 10000);
    chdir(sh->cd_params->modif_env[2]);
    apply_old(sh->cd_params->modif_env[2], tmp);
    apply_old(sh->cd_params->new_PWD[2], sh->cd_params->modif_env[2]);
    apply_old(tmp, sh->cd_params->new_PWD[2]);
    set_env(env, sh->cd_params->modif_env);
    set_env(env, sh->cd_params->new_PWD);
    sh->last_return = 0;
    return 0;
}

int go_home(char **parsed, shell_t *sh, char **env)
{
    char *actual = malloc(sizeof(char) * 10000);
    getcwd(sh->cd_params->old_cd, 10000);
    sh->cd_params->modif_env[2] = sh->cd_params->old_cd;
    set_env(env, sh->cd_params->modif_env);
    chdir(sh->cd_params->user);
    getcwd(actual, 10000);
    sh->cd_params->new_PWD[2] = actual;
    sh->last_return = 0;
    return set_env(env, sh->cd_params->new_PWD);
}

int go_outside(char **parsed, shell_t *sh, char **env)
{
    char *actual = malloc(sizeof(char) * 10000);
    getcwd(sh->cd_params->old_cd, 10000);
    sh->cd_params->modif_env[2] = sh->cd_params->old_cd;
    set_env(env, sh->cd_params->modif_env);
    chdir(parsed[1]);
    getcwd(actual, 10000);
    sh->cd_params->new_PWD[2] = actual;
    sh->last_return = 0;
    return set_env(env, sh->cd_params->new_PWD);
}
