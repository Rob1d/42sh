/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** pars the alias
*/

#include "../includes/minishell.h"

bool set_alias(char **value, shell_t *sh, char *line)
{
    FILE *fp;
    int i = 0;
    int y = 0;
    char *name_f;
    char *name_alias;
    char *value_alias;
    if (!is_str_equal(value[0], "alias")) return false;
    name_alias = strdup(line);
    printf("initial name = %s\n", name_alias);
    for (; *name_alias != ' ' && *name_alias != '\0'; ++name_alias, ++i);
    ++i;
    for(; name_alias[y] != ' ' && name_alias[y] != '\0'; ++i, ++y);
    name_alias[y] = '\0';
    ++i;
    value_alias = strdup(line);
    value_alias += i;
    printf("name alias = %s, value = %s\n", name_alias, value);
    name_f = str_concat(str_concat(sh->cd_params->user, "/"), "myshrc");
    fp = fopen(name_f, "a");
    fprintf(fp, "alias %s=\"%s\"\n", value[1], value[2]);
    fclose(fp);
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
