/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** my_cd
*/

#include "../includes/minishell.h"

void params_cd(cd *cd_params)
{
    cd_params->old_cd = malloc(sizeof(char) * 256);
    cd_params->user = malloc(sizeof(char) * 256);
    getcwd(cd_params->old_cd, 256);
    getcwd(cd_params->user, 256);
    cd_params->modif_env = malloc(sizeof(char *) * 5);
    cd_params->new_PWD = malloc(sizeof(char *) * 5);
    cd_params->modif_env[0] = "setenv";
    cd_params->modif_env[1] = "OLDPWD";
    cd_params->modif_env[2] = malloc(sizeof(char) * 256);
    cd_params->modif_env[3] = NULL;
    cd_params->new_PWD[0] = "setenv";
    cd_params->new_PWD[1] = "PWD";
    cd_params->new_PWD[2] = malloc(sizeof(char) * 256);
    cd_params->new_PWD[3] = NULL;
    apply_old(cd_params->old_cd, cd_params->modif_env[2]);
    apply_old(cd_params->user, cd_params->new_PWD[2]);
}

int my_cd(char **parsed, shell_t *sh, char **env)
{
    DIR *directory;
    if (len_env(parsed) > 2) {
        sh->last_return = 1;
        my_put_str_er("cd: Too many arguments.\n");
        return 1;
    }
    if (parsed[1] == NULL || parsed[1][0] == '~')
        return go_home(parsed, sh, env);
    if (parsed[1][0] == '-')
        return minus_cd(sh, env);
    directory = opendir(parsed[1]);
    if (directory == NULL) {
        fprintf(stderr, "%s: %s.\n", parsed[1], strerror(errno));
        sh->last_return = 1;
        return 0;
    }
    closedir(directory);
    return go_outside(parsed, sh, env);
}

int is_str_equal(char *str, char *to_test)
{
    if (str_len(str) != str_len(to_test))
        return 0;
    for (int i = 0; str[i] != '\0'; ++i)
        if (str[i] != to_test[i])
            return 0;
    return 1;
}
