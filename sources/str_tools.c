/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** str_tools
*/

#include "../includes/minishell.h"

int len_spaces_alias(char *str, int i)
{
    while ((str[i] == '\n' || str[i] == 9) && str[i] != '\0')
        ++i;
    return i;
}

char *str_concat(char *first, char *sec)
{
    char *ret = malloc(sizeof(char) * (str_len(first) + str_len(sec)) + 1);
    int i = 0;
    int j = 0;
    for (; first[i] != '\0'; ++i)
        ret[i] = first[i];
    for (; sec[j] != '\0'; ++j)
        ret[i + j] = sec[j];
    ret[i + j] = '\0';
    return ret;
}

bool str_star_with(char *str, char *str_start)
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

void my_put_str_er(char *str)
{
    write(2, str, str_len(str));
}

void error_acess(char *pars)
{
    my_put_str_er(pars);
    my_put_str_er(": Command not found.\n");
}
