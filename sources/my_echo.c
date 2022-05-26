/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** echo
*/

#include "../includes/minishell.h"

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
    if (name_var[0] == '0') {
        printf("42sh");
        return i;
    }
    for (int w = 0; env[w] != NULL; ++w)
        if (str_star_with(env[w], name_var)) {
            print_without_var(env[w]);
            return i - 1;
        }
    return 0;
}

static int check_var(char **env, char *line, shell_t *sh, int i)
{
    char *name_var = malloc(sizeof(char) * str_len(line) + 1);
    ++i;
    int j = 0;
    for (; line[i] != ' ' && line[i] != '\0' && line[i] != '"'; ++i, ++j)
        name_var[j] = line[i];
    name_var[j] = '\0';
    if (name_var[0] == '?' || name_var[0] == '0')
        return i;
    for (int w = 0; env[w] != NULL; ++w)
        if (str_star_with(env[w], name_var)) {
            free(name_var);
            return i - 1;
        }
    fprintf(stderr, "%s: Undefined variable.\n", name_var);
    free(name_var);
    exit(1);
}

static void echo_red(char **env, shell_t *sh, echo_r_t *ert)
{
    for (; ert->line[ert->i] != ert->start
    && ert->line[ert->i] != '\0'; ++ert->i) {
        if (ert->line[ert->i] == '$')
            ert->i = write_var(env, ert->line, sh, ert->i);
        else
            printf("%c", ert->line[ert->i]);
        if (ert->line[ert->i] == '\0') break;
    }
    printf("\n");exit(0);
}

bool my_echo(char **env, char *line, char **pars, shell_t *sh)
{
    int i = 0;
    char start = 0;
    int pid = 0;
    int rd = 0;
    if (!is_str_equal("echo", pars[0])) return 0;
    (*line == ' ') ? ++line : 0;
    pid = fork();
    if (pid == 0) {
        for (; *line != ' ' && *line != '\0'; ++line);
        for (; (line[i] == ' ' || line[i] == 9) && line[i] != '\0'; ++i);
        start = line[i] == '\'' || line[i] == '"' ? line[i] : '\0';
        line[i] == '\'' || line[i] == '"' ? ++i : 0;
        for (int x = i; line[x] != start && line[x] != '\0'; ++x)
            x = (line[x] == '$') ? check_var(env, line, sh, x) : x;
        echo_red(env, sh, &(echo_r_t){line, start, i});
    }
    waitpid(pid, &rd, 0);
    sh->last_return = WIFEXITED(rd) ? WEXITSTATUS(rd) : 1;
    return 1;
}