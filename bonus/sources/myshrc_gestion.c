/*
** EPITECH PROJECT, 2022
** bonus
** File description:
** gestion of the rc
*/

#include "../includes/minishell.h"

int check_command_alias(char **alias, int i, char *command)
{
    char *tmp = malloc(str_len(alias[i]) + 1);
    int j = 1;
    int w = 0;
    for (; alias[i][j - 1] != ' '; ++j);
    for (; alias[i][j + w] != '='; ++w)
        tmp[w] = alias[i][j + w];
    tmp[w] = '\0';
    if (is_str_equal(command, tmp))
        return 1;
    free(tmp);
    return 0;
}

char *extract_command_alias(char **alias, int i)
{
    int j = 1;
    int w = 0;
    char *nw_command = malloc(sizeof(char) * str_len(alias[i]));
    for (; alias[i][j - 1] != 34; ++j);
    for (; alias[i][w + j] != 34; ++w)
        nw_command[w] = alias[i][w + j];
    nw_command[w] = '\0';
    return nw_command;
}

char *as_alias(char *command)
{
    int file = open("myshrc", O_RDONLY);
    struct stat rc_stat;
    char *buf;
    char **alias;
    stat("myshrc", &rc_stat);
    buf = malloc(sizeof(char) * rc_stat.st_size + 1);
    read(file, buf, rc_stat.st_size);
    buf[rc_stat.st_size] = '\0';
    close(file);
    alias = parsing_alias(buf);
    for (int i = 0; alias[i] != NULL; ++i)
        if (check_command_alias(alias, i, command))
            return extract_command_alias(alias, i);
    return command;
}

char *read_last_line(char *line)
{
    int file = open("myshrc_h", O_RDONLY);
    struct stat rc_stat;
    char *buf;
    char **parsed;
    int i = 0;
    int cp = 0;
    for (int j = 0; line[j] != '\0'; ++j)
        line[j] == '!' ? ++cp : 0;
    stat("myshrc_h", &rc_stat);
    buf = malloc(sizeof(char) * rc_stat.st_size + 1);
    read(file, buf, rc_stat.st_size);
    buf[rc_stat.st_size] = '\0';
    close(file);
    parsed = parsing_alias(buf);
    for (; parsed[i] != NULL; ++i);
    return parsed[i - cp - 1];
}

void write_to_rc(char *command)
{
    int file = open("myshrc_h", O_APPEND | O_WRONLY);
    write(file, command, str_len(command));
    write(file, "\n", 1);
    close(file);
}
