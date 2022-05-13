/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** pars the path
*/

#include "../includes/minishell.h"

int len_spaces_path(char *str, int i)
{
    while ((str[i] == ':') && str[i] != '\0')
        ++i;
    return i;
}

int count_path(char *str)
{
    int nb = 1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ':') {
            ++nb;
            i = len_spaces_path(str, i);
        }
        ++i;
    }
    return nb;
}

int len_path(char *str, int i)
{
    int cp = 0;
    while (str[i] != 9 && str[i] != ':' && str[i] != '\0') {
        ++i;
        ++cp;
    }
    return cp;
}

int check_start(char *str, int i)
{
    for (; str[i] != '='; ++i);
    return i + 1;
}

char **parsing_path(char *str)
{
    char **parsed = malloc(sizeof(char *) * (count_path(str) + 5));
    int cp_parsed = 0;
    int cp_tmp = 0;
    int j = len_spaces_path(str, 0);
    j = check_start(str, j);
    for (int i = j; str[i] != '\0'; ++i) {
        parsed[cp_parsed] = malloc(sizeof(char) * len_path(str, i) + 1);
        while (str[i] != 9 && str[i] != ':' && str[i] != '\0') {
            parsed[cp_parsed][cp_tmp] = str[i];
            ++cp_tmp;
            ++i;
        }
        parsed[cp_parsed][cp_tmp] = '\0';
        ++cp_parsed;
        cp_tmp = 0;
        i = len_spaces_path(str, i) - 1;
    }
    parsed[cp_parsed] = "";
    parsed[cp_parsed + 1] = NULL;
    return parsed;
}
