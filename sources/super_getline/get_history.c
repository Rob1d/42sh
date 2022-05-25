/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** get_history
*/

#include "../../includes/minishell.h"

void my_db_rev(char **db)
{
    int i = 0;
    int j = 0;
    char *temp;
    while (db[i] != NULL)
        ++i;
    --i;
    while (i > j){
        temp = db[j];
        db[j] = db[i];
        db[i] = temp;
        --i;
        ++j;
    }
}

static char *received_line(FILE *fp)
{
    char *tmp = NULL;
    size_t len = 0;
    if (getline(&tmp, &len, fp) == -1)
        return NULL;
    tmp[len - 1] = '\0';
    return tmp;
}

static bool is_empty(char *str)
{
    int i = 0;
    for (; str[i] != '\0' && (str[i] == ' ' ||
    str[i] == '\t' || str[i] == '\n'); ++i);
    return str[i] == '\0' ? false : true;
}

static char *without_comments(FILE *fp)
{
    char *tmp = received_line(fp);
    if (tmp == NULL)
        return NULL;
    while (!is_empty(tmp)) {
        free(tmp);
        tmp = received_line(fp);
        if (tmp == NULL)
            return NULL;
    }
    return tmp;
}

char **my_db_copy(char *db[])
{
    int i = 0;
    char **ret;
    for (;db[i] != NULL; ++i);
    ret = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; db[j] != NULL; ++j)
        ret[j] = db[j];
    ret[i] = NULL;
    return ret;
}

char **received_input(shell_t *sh)
{
    char *input[1024];
    char *name_f = str_concat(str_concat
    (sh->cd_params->user, "/"), "myshrc_h");
    FILE *fp = fopen(name_f, "r");
    if (fp == NULL) return NULL;
    int cp = 0;
    char *tmp = without_comments(fp);
    while (tmp != NULL) {
        input[cp] = strdup(tmp);
        input[cp][strlen(input[cp]) - 1] = '\0';
        ++cp;
        free(tmp);
        tmp = without_comments(fp);
    }
    input[cp] = NULL;
    fclose(fp);
    my_db_rev(input);
    return my_db_copy(input);
}