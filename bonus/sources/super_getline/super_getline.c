/*
** EPITECH PROJECT, 2022
** bonus
** File description:
** super_getline
*/

#include "../../includes/minishell.h"

void putstr(char const *str)
{
    write(1, str, strlen(str));
}

static int check_arrows(history_t *hs, int c, int *i, char **password)
{
    int tmp_i = *i;
    if (c == 27) {
        c = getchar();
        c = getchar();
        for (int w = 0; w < 4; ++w)
            write(1, "\b \b", 3);
        if (c == 'A' && hs->actual_history < hs->len - 1) {
            for (int w = 0; w < *i; ++w)
                write(1, "\b \b", 3);
            *i = 0;
            ++hs->actual_history;
            putstr(hs->history[hs->actual_history]);
            *i = strlen(hs->history[hs->actual_history]);
            *password = strdup(hs->history[hs->actual_history]);
            *password = realloc(*password, 128);
        }
        if (c == 'B' && hs->actual_history > 0) {
            for (int w = 0; w < *i; ++w)
                write(1, "\b \b", 3);
            *i = 0;
            --hs->actual_history;
            putstr(hs->history[hs->actual_history]);
            *i = strlen(hs->history[hs->actual_history]);
            *password = strdup(hs->history[hs->actual_history]);
            *password = realloc(*password, 128);
        }
        if (c == 'D' && *i > 0) {
            write(1, "\b\b", 2);
            write(1, &password[tmp_i], 1);
        }
        if (c == 'C')
            write(1, &password[tmp_i - 1], 1);
        return 1;
    }
    return 0;
}

static history_t *init_history(char **history)
{
    int i = 0;
    history_t *hs = malloc(sizeof(history_t));
    for (; history[i] != NULL; ++i);
    hs->len = i;
    hs->history = history;
    hs->actual_history = -1;
    return hs;
}

static void super_getline_red(char c, int *i, char *password, int *check, shell_t *sh)
{
    int tmp_i = *i;
    if ((c == 127 || c == 8)) {
        for (int a = 0; a < (tmp_i != 0 ? 3 : 2); ++a)
            write(1, "\b \b", 3);
        if (tmp_i != 0)
            password[--tmp_i] = 0;
    } else {
        !*check ? write(1, "\b", 1) : 0;
        !*check ? write(1, &c, 1) : 0;
        if (!*check)
            password[tmp_i++] = c;
        *check = 0;
    }
    *i = tmp_i;
}

char *get_complete(char *password, int *i, int *check, shell_t *sh, char c)
{
    int tmp_i = *i;
    if (c == '\t') {
        *check = 1;
        write(1, "\r", 1);
        printf(" ");
        special_output(sh);
        password[tmp_i] = '\0';
        password = autocompeltion(password);
        tmp_i = strlen(password);
        printf("%s", password);
        password[strlen(password)] = ' ';
    }
    *i = tmp_i;
    return password;
}

static char *real_get(char **history, shell_t *sh)
{
    int c = 0;
    int i = 0;
    int check = 0;
    int size_malloc = 128;
    history_t *hs = init_history(history);
    char *password = malloc(sizeof(char) * size_malloc);
    while((c = getchar()) != '\n') {
        password = get_complete(password, &i, &check, sh, c);
        check = check_arrows(hs, c, &i, &password);
        super_getline_red(c, &i, password, &check, sh);
        if (i >= (size_malloc) - 1) {
            size_malloc += 128;
            password = (char *)realloc(password, sizeof(char) * size_malloc);
        }
    }
    password[i] = '\0';
    for (int x = 0; hs->history[x] != NULL; ++x)
        free(hs->history[x]);
    free(hs->history);
    return password;
}

char *super_getline(char **history, shell_t *sh)
{
    char *ret;
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    if (tcsetattr( STDIN_FILENO, TCSANOW, &newt) != 0) {
        perror("tcsetattr");
        return (NULL);
    }
    ret = real_get(history, sh);
    if (tcsetattr( STDIN_FILENO, TCSANOW, &oldt) != 0) {
        perror("tcsetattr");
        return (NULL);
    }
    return ret;
}
