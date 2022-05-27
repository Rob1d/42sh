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
    int i = 0;
    for (; str[i] != '\0'; ++i)
        new_str[i] = str[i];
    new_str[i] = '\0';
    directory = opendir(new_str);
    if (directory == NULL)
        return 0;
    my_put_str_er(str);
    my_put_str_er(": Permission denied.\n");
    closedir(directory);
    return 1;
}

int launch_command(char **env, char **pars, shell_t *sh)
{
    int pid = 0;
    int rd = 0;
    char *command = as_path(env, pars[0]);
    if (command[0] == '\0') {
        sh->last_return = 0;return 1;
    }
    if (can_open(pars[0])) {
        sh->last_return = 1;return 1;
    }
    pars = command_with_color(pars, sh);pid = fork();
    if (pid == 0) {
        execve(command, pars, env);
        (errno == ENOEXEC) ? fprintf(stderr, "%s: "
        "Exec format error. Wrong Architecture.\n", pars[0]) : 0;
    }
    (waitpid(pid, &rd, WUNTRACED) == -1) ? exit(84) : 0;
    sh->last_return = WIFEXITED(rd) ? WEXITSTATUS(rd) : 1;verify_return(rd);
    return 0;
}

static int process_commands_red
(char *line, char **env, shell_t *sh, bool is_piped)
{
    char **pars = parsing(line);
    if (set_alias(pars, sh, line)) return 1;
    if (my_echo(env, line, pars, sh)) return 1;
    if (is_builtin_name(pars[0]) && is_piped) return 1;
    (is_str_equal(pars[0], "exit")) ? exit(0) : 0;
    if (is_str_equal(pars[0], "cd")) {
        my_cd(pars, sh, env);
        return 1;
    }
    if (is_env(env, pars, sh)) return 1;
    if (left_redirection(line, env, sh)) return 1;
    if (set_variable(pars, sh)) return 1;
    return launch_command(env, pars, sh);
}

int process_commands(char *line, char **env, shell_t *sh, bool is_piped)
{
    char *tmp_line = as_alias(line, sh);
    while (!is_str_equal(tmp_line, line)) {
        line = strdup(tmp_line);
        tmp_line = as_alias(line, sh);
    }
    line = as_var(line, sh, env);
    if (line == NULL) return 1;
    for (int i = 0; line[i] != '\0'; ++i)
        if (line[i] == '(') {
            printf("4\n");
            return 1;
        }
    if (is_str_equal(line, "ui")) return 1;
    if (right_redirection(line, env, sh)) return 1;
    if (pipe_gestion(line, env, sh)) return 1;
    if (display_history(line, sh)) return 1;
    return process_commands_red(line, env, sh, is_piped);
}
