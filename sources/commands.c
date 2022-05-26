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

int process_commands(char *line, char **env, shell_t *sh, bool is_piped)
{
    char **pars;
    line = as_alias(line, sh);
    if (is_str_equal(line, "ui")) return 1;
    if (right_redirection(line, env, sh)) return 1;
    if (pipe_gestion(line, env, sh)) return 1;
    pars = parsing(line);
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

static void verify_command_red(char **line, shell_t *sh)
{
    free(line);
    sh->len_separator = 0;
    free(sh->separator_type);
    sh->separator_type = malloc(sizeof(int));
}

bool is_empty_command(char const *command)
{
    for (int i = 0; command[i] != '\0'; ++i)
        if (command[i] != ' ' && command[i] != '\t')
            return false;
    return true;
}

void check_len_command(char **line, shell_t *sh)
{
    int cp = 0;
    for (int i = 0; line[i] != NULL; ++i)
        !is_empty_command(line[i]) || sh->separator_type[i] == 0 ? ++cp : 0;
    if (sh->len_separator >= cp) {
        sh->len_separator = -1;
        fprintf(stderr, "Invalid null command.\n");
        sh->last_return = 1;
    }
}

void verify_command(char **env, shell_t *sh)
{
    char **line = wait_commands(sh, env);
    int tmp = 0;
    bool last_return = true;
    check_len_command(line, sh);
    for (int i = 0; i <= sh->len_separator; ++i) {
        last_return = sh->len_separator > 0 && (sh->separator_type[i - 1] == 2
        && !last_return) ? false : true;
        tmp = if_statement(line[i], env, sh);
        if (((i == 0 || sh->separator_type[i - 1] == 0 ||
        (sh->separator_type[i - 1] == 1 && sh->last_return != 0) ||
        (sh->separator_type[i - 1] == 2 && sh->last_return == 0))) && last_return) {
            line[i] += tmp;
            line[i] = line[i][0] == '\0' ? strdup("ui") : line[i];
            process_commands(line[i], env, sh, false);
            line[i] -= is_str_equal(line[i], "ui") ? 0 : tmp;
            last_return = 1;
        } else
            last_return = false;
        free(line[i]);
    }
    verify_command_red(line, sh);
}
