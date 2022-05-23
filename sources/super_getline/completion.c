/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** autocompeltion
*/

#include "../../includes/minishell.h"

static bool str_start_with(char *str, char *start)
{
    if (str_len(str) < strlen(start))
        return false;
    for (int i = 0; start[i] != '\0'; ++i)
        if (start[i] != str[i])
            return false;
    return true;
}

static char *good_files(char *search)
{
    char *ret;
    DIR *dir = opendir(".");
    struct dirent *tmp = readdir(dir);
    while (tmp != NULL) {
        if (str_start_with(tmp->d_name, search)) {
            ret = strdup(tmp->d_name);
            closedir(dir);
            return ret;
        }
        tmp = readdir(dir);
    }
    closedir(dir);
    return NULL;
}

char *autocompeltion(char *inital_line)
{
    char *end_of_line = strdup(inital_line);
    int i = strlen(inital_line);
    char *concat_name;
    for (; i >= 0 && inital_line[i] != ' '; --i);
    end_of_line += i + 1;
    concat_name = good_files(end_of_line);
    end_of_line -= i + 1;
    end_of_line[i + 1] = '\0';
    if (concat_name != NULL) {
        end_of_line = str_concat(end_of_line, concat_name);
        end_of_line = realloc(end_of_line, sizeof(char) * 128);
        free(concat_name);
        return end_of_line;
    }
    return inital_line;
}