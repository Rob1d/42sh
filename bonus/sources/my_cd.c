/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** my_cd
*/

#include "../includes/minishell.h"

void params_cd(cd *cd_params)
{
    cd_params->old_cd = get_current_dir;
    cd_params->user = malloc(sizeof(char) * 10000);
    getcwd(cd_params->old_cd, 10000);
    getcwd(cd_params->user, 10000);
    cd_params->modif_env = malloc(sizeof(char *) * 5);
    cd_params->new_PWD = malloc(sizeof(char *) * 5);
    cd_params->modif_env[0] = "setenv";
    cd_params->modif_env[1] = "OLDPWD";
    cd_params->modif_env[2] = malloc(sizeof(char) * 10000);
    cd_params->modif_env[3] = NULL;
    cd_params->new_PWD[0] = "setenv";
    cd_params->new_PWD[1] = "PWD";
    cd_params->new_PWD[2] = malloc(sizeof(char) * 10000);
    cd_params->new_PWD[3] = NULL;
    apply_old(cd_params->old_cd, cd_params->modif_env[2]);
    apply_old(cd_params->user, cd_params->new_PWD[2]);
}

int my_cd(char **parsed, cd *cd_params, char **env)
{
    DIR *directory;
    if (len_env(parsed) > 2) {
        my_put_str_er("cd: Too many arguments.\n");
        return 1;
    }
    if (parsed[1] == NULL || parsed[1][0] == '~')
        return go_home(parsed, cd_params, env);
    if (parsed[1][0] == '-')
        return minus_cd(cd_params, env);
    directory = opendir(parsed[1]);
    if (directory == NULL) {
        my_put_str_er(parsed[1]);
        my_put_str_er(": ");
        my_put_str_er(strerror(errno));
        write(2, ".\n", 2);
    }
    closedir(directory);
    return go_outside(parsed, cd_params, env);
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
