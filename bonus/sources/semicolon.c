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

void semicolon(char *command, char **re)
{
    int cp_re = 0;
    int i = 0;
    int cp = 0;
    command = first_semicolon(command);
    re[cp_re] = malloc(sizeof(char) * str_len(command) + 2);
    for (; command[i] != '\0'; ++i) {
        if (command[i] == ';' && no_space(command, &i)) {
            re[cp_re][cp] = '\0';
            ++cp_re;
            re[cp_re] = malloc(sizeof(char) * str_len(command) + 2);
            cp = 0;
        } else if (command[i] != ';'){
            re[cp_re][cp] = command[i];
            ++cp;
        } else
            --i;
    }
    re[cp_re][cp] = '\0';
    re[cp_re + 1] = NULL;
}
