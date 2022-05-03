/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** as path
*/

#include "../includes/minishell.h"

int is_good_env(char *path, char *command)
{
    int i = 0;
    int j = 0;
    char *tmp = malloc(sizeof(char) * ((str_len
    (path) + str_len(command))) + 5);
    for (; path[i] != '\0'; ++i)
        tmp[i] = path[i];
    tmp[i] = '/';
    ++i;
    for (; command[j] != '\0'; ++j)
        tmp[i + j] = command[j];
    tmp[i + j] = '\0';
    if (!access(tmp, R_OK) && !access(tmp, X_OK))
        return 1;
    return 0;
}

int witch_env(char *command, char **path)
{
    for (int i = 0; path[i] != NULL; ++i)
        if (is_good_env(path[i], command))
            return i;
    return -1;
}

char *concat_commands(char *command, char *path)
{
    int i = 0;
    int j = 0;
    char *tmp = malloc(sizeof(char) * ((str_len
    (path) + str_len(command))) + 5);
    for (; path[i] != '\0'; ++i)
        tmp[i] = path[i];
    tmp[i] = '/';
    ++i;
    for (; command[j] != '\0'; ++j)
        tmp[i + j] = command[j];
    tmp[i + j] = '\0';
    return tmp;
}

char *as_path(char **env, char *command)
{
    int len = 0;
    char **path;
    int nb_path = -1;
    for (; (env[len][0] != 'P' || env[len][1] != 'A' || env[len]
    [2] != 'T' || env[len][3] != 'H') && env[len] != NULL; ++len);
    if (env[len] == NULL)
        return 0;
    path = parsing_path(env[len]);
    nb_path = witch_env(command, path);
    if (nb_path != -1)
        return concat_commands(command, path[nb_path]);
    if (!access(command, F_OK))
        return command;
    my_put_str_er(command);
    my_put_str_er(": Command not found.\n");
    return "";
}
