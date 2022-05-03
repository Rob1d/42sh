/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** split commands
*/

#include "../includes/minishell.h"

static int len_pipe(char *str, int i)
{
    while ((str[i] == '|' || str[i] == 9) && str[i] != '\0')
        ++i;
    return i;
}

static int count_pipe(char *str)
{
    int nb = 1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '|') {
            ++nb;
            i = len_pipe(str, i);
        }
        ++i;
    }
    return nb;
}

static int len_word_pipe(char *str, int i)
{
    int cp = 0;
    while (str[i] != 9 && str[i] != '|' && str[i] != '\0') {
        ++i;
        ++cp;
    }
    return cp;
}

char **split_commands(char *str)
{
    char **parsed = malloc(sizeof(char *) * (count_pipe(str) + 2));
    int cp_parsed = 0;
    int cp_tmp = 0;
    int j = 0;
    j = len_pipe(str, 0);
    for (int i = j; str[i] != '\0'; ++i) {
        parsed[cp_parsed] = malloc(sizeof(char) * len_word_pipe(str, i) + 1);
        while (str[i] != 9 && str[i] != '|' && str[i] != '\0') {
            parsed[cp_parsed][cp_tmp] = str[i];
            ++cp_tmp;
            ++i;
        }
        parsed[cp_parsed][cp_tmp] = '\0';
        ++cp_parsed;
        cp_tmp = 0;
        i = len_pipe(str, i) - 1;
    }
    parsed[cp_parsed] = NULL;
    check_spaces(parsed);
    return parsed;
}
