/*
** EPITECH PROJECT, 2022
** mishell
** File description:
** parsing
*/

#include "../includes/minishell.h"

int str_len(char *str)
{
    int i = 0;
    for (;str[i] != '\0'; ++i);
    return i;
}

int len_spaces(char *str, int i)
{
    while ((str[i] == ' ' || str[i] == 9) && str[i] != '\0')
        ++i;
    return i;
}

int count_words(char *str)
{
    int nb = 1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            ++nb;
            i = len_spaces(str, i);
        } else
            ++i;
    }
    return nb;
}

int len_word(char *str, int i)
{
    int cp = 0;
    while (str[i] != 9 && str[i] != ' ' && str[i] != '\0') {
        ++i;
        ++cp;
    }
    return cp;
}

char **parsing(char *str)
{
    char **parsed = malloc(sizeof(char *) * (count_words(str) + 2));
    int cp_parsed = 0;
    int cp_tmp = 0;
    int j = 0;
    j = len_spaces(str, 0);
    for (int i = j; str[i] != '\0'; ++i) {
        parsed[cp_parsed] = malloc(sizeof(char) * len_word(str, i) + 1);
        while (str[i] != 9 && str[i] != ' ' && str[i] != '\0') {
            parsed[cp_parsed][cp_tmp] = str[i];
            ++cp_tmp;
            ++i;
        }
        parsed[cp_parsed][cp_tmp] = '\0';
        ++cp_parsed;
        cp_tmp = 0;
        i = len_spaces(str, i) - 1;
    }
    parsed[cp_parsed] = NULL;
    return parsed;
}
