/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** semicolon
*/

#include "../includes/minishell.h"

static bool no_space(char *command, int *i)
{
    int tmp_i = i[0] + 1;
    for (; command[tmp_i] != '\0' && command[tmp_i] != ';'; ++tmp_i)
        if (command[tmp_i] != ' ' && command[tmp_i] != 9)
            return true;
    ++*i;
    return false;
}

static char *first_semicolon(char *command)
{
    char *tmp = "ui";
    int i = 0;
    for (; command[i] != '\0' && (command[i] == 9 || command
    [i] == ' ' || command[i] == ';'); ++i);
    if (str_len(command) <= i)
        return tmp;
    command += i;
    return command;
}
static int which_separator(char *command, int i)
{
    if (command[i] == '\0' || command[i + 1] == '\0')
        return -1;
    if (command[i] == ';')
        return 0;
    if (command[i] == '|' && command[i + 1] == '|')
        return 1;
    if (command[i] == '&' && command[i + 1] == '&')
        return 2;
    return -1;
}

char **semicolon(char *command, shell_t *sh)
{
    int i = 0;
    int cp = 0;
    char **re = malloc(sizeof(char *) * 2);
    sh->len_separator = 0;
    sh->separator_type = malloc(sizeof(int));
    command = first_semicolon(command);
    re[0] = malloc(sizeof(char) * str_len(command) + 2);
    for (; command[i] != '\0'; ++i) {
        if (which_separator(command, i) != -1 && no_space(command, &i)) {
            re[sh->len_separator][cp] = '\0';
            sh->separator_type[sh->len_separator] = which_separator(command, i);
            sh->len_separator++;
            sh->separator_type != 0 ? ++i : 0;
            re = realloc(re, (sizeof(char *) * (sh->len_separator + 2)));
            sh->separator_type = realloc(sh->separator_type, (sizeof(int) * (sh->len_separator + 2)));
            re[sh->len_separator] = malloc(sizeof(char) * str_len(command) + 2);
            cp = 0;
        } else if (command[i] != ';'){
            re[sh->len_separator][cp] = command[i];
            ++cp;
        } else
            --i;
    }
    re[sh->len_separator][cp] = '\0';
    re[sh->len_separator + 1] = NULL;
    return re;
}
