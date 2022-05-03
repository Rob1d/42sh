/*
** EPITECH PROJECT, 2022
** commands
** File description:
** send commands
*/

#include "../includes/minishell.h"

int can_open(char *str)
{
    char *new_str = malloc(sizeof(char) * strlen(str) + 1);
    DIR *directory;
    int i = 2;
    if (str[0] != '.' || str[1] != '/')
        return 0;
    for (; str[i] != '\0'; ++i)
        new_str[i - 2] = str[i];
    new_str[i - 2] = '\0';
    directory = opendir(new_str);
    if (directory == NULL)
        return 0;
    my_put_str_er(str);
    my_put_str_er(": Permission denied.\n");
    closedir(directory);
    return 1;
}

void error_acess(char *pars)
{
    my_put_str_er(pars);
    my_put_str_er(": Command not found.\n");
}

int launch_command(char **env, char **pars)
{
    int pid = 0;
    int rd = 0;
    char *command = as_path(env, pars[0]);
    if (command[0] == '\0')
        return 1;
    if (can_open(pars[0]))
        return 1;
    pid = fork();
    if (pid == 0) {
        execve(command, pars, env);
        if (errno == ENOEXEC)
            my_put_str_er("Exec format error. Wrong Architecture.\n");
    }
    if (waitpid(pid, &rd, 0) == -1)
        exit(84);
    verify_return(rd);
    return 0;
}

int process_commands(char *line, char **env, cd *cd_params, bool is_piped)
{
    char **pars;
    line = as_alias(line);
    if (line[0] == '!')
        line = read_last_line(line);
    if (is_str_equal(line, "ui"))
        return 1;
    if (right_redirection(line, env, cd_params))
        return 1;
    if (pipe_gestion(line, env, cd_params))
        return 1;
    pars = parsing(line);
    if (is_builtin_name(pars[0]) && is_piped)
        return 1;
    (is_str_equal(pars[0], "exit")) ? exit(0) : 0;
    if (is_str_equal(pars[0], "cd")) {
        my_cd(pars, cd_params, env);
        return 1;
    }
    if (is_env(env, pars))
        return 1;
    if (left_redirection(line, env, cd_params))
        return 1;
    launch_command(env, pars);
    return 0;
}

int verify_command(char **env, cd *cd_params)
{
    char **line = wait_commands();
    for (int i = 0; line[i] != NULL; ++i) {
        process_commands(line[i], env, cd_params, false);
    }
    return 0;
}
