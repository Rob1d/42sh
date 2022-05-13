/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** pars the alias
*/

#include "../includes/minishell.h"

bool set_alias(char **value)
{
    FILE *fp;
    int i = 0;
    if (!is_str_equal(value[0], "setalias"))
        return false;
    for (; value[i] != NULL; ++i);
    if (i != 3) {
        fprintf(stderr, "setalias: Too many arguments.\n");
        return 1;
    }
    fp = fopen("myshrc", "a");
    fprintf(fp, "alias %s=\"%s\"\n", value[1], value[2]);
    fclose(fp);
    printf("good !\n");
    return true;
}

int len_spaces_alias(char *str, int i)
{
    while ((str[i] == '\n' || str[i] == 9) && str[i] != '\0')
        ++i;
    return i;
}

int count_words_alias(char *str)
{
    int nb = 1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            ++nb;
            i = len_spaces_alias(str, i);
        } else
            ++i;
    }
    return nb;
}

int len_word_alias(char *str, int i)
{
    int cp = 0;
    while (str[i] != 9 && str[i] != '\n' && str[i] != '\0') {
        ++i;
        ++cp;
    }
    return cp;
}

char **parsing_alias(char *str)
{
    char **parsed = malloc(sizeof(char *) * (count_words_alias(str) + 2));
    int cp_parsed = 0;
    int cp_tmp = 0;
    int j = 0;
    j = len_spaces_alias(str, 0);
    for (int i = j; str[i] != '\0'; ++i) {
        parsed[cp_parsed] = malloc(sizeof(char) * len_word_alias(str, i) + 1);
        while (str[i] != '\n' && str[i] != '\0') {
            parsed[cp_parsed][cp_tmp] = str[i];
            ++cp_tmp;
            ++i;
        }
        parsed[cp_parsed][cp_tmp] = '\0';
        ++cp_parsed;
        cp_tmp = 0;
        i = len_spaces_alias(str, i) - 1;
    }
    parsed[cp_parsed] = NULL;
    return parsed;
}
