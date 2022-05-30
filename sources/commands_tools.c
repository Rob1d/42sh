/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** tools for the commands
*/

#include "../includes/minishell.h"

static void remove_quote(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if ((command[i] == '"' || command[i] == '\'')
        && (i > 0 && command[i - 1] != '\\'))
            command[i] = ' ';
        if ((command[i] == '"' || command[i] == '\'')
        && (i > 0 && command[i - 1] == '\\'))
            command[i - 1] = ' ';
    }
}

char **wait_commands(shell_t *sh, char **env)
{
    char *buf = NULL;
    char **re;
    size_t line_size = 0;
    char **history = received_input(sh, true);
    sh->all_mode ? special_output(sh) : 0;
    if (history != NULL && sh->all_mode) {
        buf = super_getline(history, sh);
        line_size = strlen(buf);
    } else {
        line_size = getline(&buf, &line_size, stdin);
        if (line_size == -1)
            exit(0);
        buf[line_size - 1] = '\0';
    }
    if (line_size == 1) buf = strdup("ui");
    remove_quote(buf);
    write_to_rc(buf, sh);
    buf = check_bactricks(buf, env, sh);
    re = semicolon(buf, sh, 0, 0);
    return re;
}

char *put_bin(char *command)
{
    char *full_command = malloc(sizeof(char) * str_len(command) + 6);
    char *bin = "/bin/";
    for (int i = 0; i < 5; ++i)
        full_command[i] = bin[i];
    for (int i = 0; command[i] != '\0'; ++i)
        full_command[i + 5] = command[i];
    return full_command;
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
