/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** pars the alias
*/

#include "../includes/minishell.h"

void set_alias_red(char *line, int i, shell_t *sh, char *name_alias)
{
    char *value_alias = strdup(line) + i;
    char *tmp_f = str_concat(sh->cd_params->user, "/");
    char *name_f = str_concat(tmp_f, "myshrc");
    FILE *fp = fopen(name_f, "a");
    fprintf(fp, "alias %s=\"%s\"\n", name_alias, value_alias);
    fclose(fp);
    value_alias -= i;
    free(value_alias);
    free(tmp_f);
    free(name_f);
}

bool set_alias(char **value, shell_t *sh, char *line)
{
    FILE *fp;
    int i = 0;
    int y = 0;
    char *name_f;
    char *name_alias;
    char *value_alias;
    char *tmp_f;
    if (!is_str_equal(value[0], "alias")) return false;
    name_alias = strdup(line);
    for (; *name_alias != ' ' && *name_alias != '\0'; ++name_alias, ++i);
    ++i;
    ++name_alias;
    for (; name_alias[y] != ' ' && name_alias[y] != '\0'; ++i, ++y);
    name_alias[y] = '\0';
    ++i;
    set_alias_red(line, i, sh, name_alias);
    return true;
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
