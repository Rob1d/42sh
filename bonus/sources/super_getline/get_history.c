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
        temp = strdup(db[j]);
        db[j] = strdup(db[i]);
        db[i] = strdup(temp);
        --i;
        ++j;
    }
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
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

char **received_input(void)
{
    char **input = malloc(sizeof(char *) + 1);
    if (input == NULL) return NULL;
    FILE *fp = fopen("myshrc_h", "r");
    if (fp == NULL) return NULL;
    int cp = 0;
    char *tmp = without_comments(fp);
    while (tmp != NULL) {
        input[cp] = strdup(tmp);
        input[cp][strlen(input[cp]) - 1] = '\0';
        ++cp;
        free(tmp);
        tmp = without_comments(fp);
        input = realloc(input, (sizeof(char * ) * (cp + 1)));
        if (input == NULL) return NULL;
    }
    input[cp] = NULL;
    fclose(fp);
    my_db_rev(input);
    return input;
}