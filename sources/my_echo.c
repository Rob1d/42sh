/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** echo
*/

#include "../includes/minishell.h"

static bool str_star_with(char *str, char *str_start)
{
    int i = 0;
    if (str_len(str) < str_len(str_start))
        return false;
    for (; str_start[i] != '\0'; ++i)
        if (str[i] != str_start[i])
            return false;
    if (str[i] != '=')
        return false;
    return true;
}

static void print_without_var(char *var)
{
    int i = 0;
    for (; var[i] != '=' && var[i] != '\0'; ++i);
    (var[i] != '\0') ? ++i : 0;
    for (; var[i] != '\0'; ++i)
        printf("%c", var[i]);
}

static int write_var(char **env, char *line, shell_t *sh, int i)
{
    char *name_var = malloc(sizeof(char) * str_len(line) + 1);
    ++i;
    int j = 0;
    for (; line[i] != ' ' && line[i] != '\0'; ++i, ++j)
        name_var[j] = line[i];
    name_var[j] = '\0';
    if (name_var[0] == '?') {
        printf("%d", sh->last_return);
        return i;
    }
    for (int w = 0; env[w] != NULL; ++w)
        if (str_star_with(env[w], name_var)) {
            print_without_var(env[w]);
            return i;
        }
    fprintf(stderr, "%s: Undefined variable.\n", name_var);
    exit(1);
}

bool my_echo(char **env, char *line, char **pars, shell_t *sh)
{
    int i = 0;
    char start = 0;
    int pid = 0;
    int rd = 0;
    if (!is_str_equal("echo", pars[0]))
        return 0;
    pid = fork();
    if (pid == 0) {
        for (; *line != ' ' && *line != '\0'; ++line);
        for (; (line[i] == ' ' || line[i] == 9) && line[i] != '\0'; ++i);
        start = line[i] == '\'' || line[i] == '"' ? line[i] : '\0';
        line[i] == '\'' || line[i] == '"' ? ++i : 0;
        for (; line[i] != start && line[i] != '\0'; ++i) {
            if (line[i] == '$')
                i = write_var(env, line, sh, i);
            else
                printf("%c", line[i]);
        }
        printf("\n");
        exit(0);
    }
    waitpid(pid, &rd, 0);
    sh->last_return = WIFEXITED(rd) ? WEXITSTATUS(rd) : 1;
    return 1;
}