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

void error_acess(char *pars)
{
    my_put_str_er(pars);
    my_put_str_er(": Command not found.\n");
}

char **command_with_color(char **pars, shell_t *sh)
{
    char *commands[] = {"ls", "grep", NULL};
    int j = 0;
    if (!sh->all_mode) return pars;
    for (; pars[j] != NULL; ++j);
    for (int i = 0; commands[i] != NULL; ++i)
        if (is_str_equal(pars[0], commands[i])) {
            pars = realloc(pars, sizeof(char *) * (j + 2));
            pars[j] = "--color=auto";
            pars[j + 1] = NULL;
            return pars;
        }
    return pars;
}

int launch_command(char **env, char **pars, shell_t *sh)
{
    int pid = 0;
    int rd = 0;
    char *command = as_path(env, pars[0]);
    if (command[0] == '\0') {
        sh->last_return = 0;
        return 1;
    }
    if (can_open(pars[0])) {
        sh->last_return = 1;
        return 1;
    }
    pars = command_with_color(pars, sh);
    pid = fork();
    if (pid == 0) {
        execve(command, pars, env);
        if (errno == ENOEXEC)
            my_put_str_er("Exec format error. Wrong Architecture.\n");
    }
    if (waitpid(pid, &rd, WUNTRACED) == -1)
        exit(84);
    sh->last_return = WIFEXITED(rd) ? WEXITSTATUS(rd) : 1;
    verify_return(rd);
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
    return launch_command(env, pars, sh);
}

int verify_command(char **env, shell_t *sh)
{
    char **line = wait_commands(sh, env);
    int tmp = if_statement(line[0], env, sh);
    if (sh->len_separator == 0) {
        line[0] += tmp;
        line[0] = line[0][0] == '\0' ? strdup("ui") : line[0];
        process_commands(line[0], env, sh, false);
        line[0] -= is_str_equal(line[0], "ui") ? 0 : tmp;
        free(line[0]);free(line);
        return 1;
    }
    for (int i = 0; i <= sh->len_separator; ++i) {
        tmp = if_statement(line[i], env, sh);
        if (((i == 0 || sh->separator_type[i - 1] == 0 ||
        (sh->separator_type[i - 1] == 1 && sh->last_return != 0) ||
        (sh->separator_type[i - 1] == 2 && sh->last_return == 0)))) {
            line[i] += tmp;
            line[i] = line[i][0] == '\0' ? strdup("ui") : line[i];
            process_commands(line[i], env, sh, false);
            line[i] -= is_str_equal(line[i], "ui") ? 0 : tmp;
        }
        free(line[i]);
    }
    free(line);sh->len_separator = 0;free(sh->separator_type);
    sh->separator_type = malloc(sizeof(int));
    return 0;
}
