/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** display all the aliaes
*/

#include "../includes/minishell.h"

static void show_command_alias(char **alias, int i)
{
    char *tmp = malloc(str_len(alias[i]) + 1);
    char *value = extract_command_alias(alias, i);
    int j = 1;
    int w = 0;
    for (; alias[i][j - 1] != ' '; ++j);
    for (; alias[i][j + w] != '='; ++w)
        tmp[w] = alias[i][j + w];
    tmp[w] = '\0';
    printf("%s\t%s\n", tmp, value);
    free(tmp);
}

void display_alias(shell_t *sh)
{
    char *name_f = str_concat(str_concat(sh->cd_params->user, "/"), "myshrc");
    int file = open(name_f, O_RDONLY);
    struct stat rc_stat;
    char *buf;
    char **alias;
    if (stat(name_f, &rc_stat) == -1) return;
    buf = malloc(sizeof(char) * rc_stat.st_size + 1);
    read(file, buf, rc_stat.st_size);
    buf[rc_stat.st_size] = '\0';
    close(file);
    alias = parsing_alias(buf);
    for (int i = 0; alias[i] != NULL; ++i)
        show_command_alias(alias, i);
    sh->last_return = 0;
}