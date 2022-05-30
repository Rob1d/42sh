/*
** EPITECH PROJECT, 2022
** bonus
** File description:
** super_getline
*/

#include "../../includes/minishell.h"

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

static void super_getline_red(char *password, shell_t *sh, sp_get_t *sgt)
{
    int tmp_i = sgt->i;
    if ((sgt->c == 127 || sgt->c == 8)) {
        for (int a = 0; a < (tmp_i != 0 ? 3 : 2); ++a)
            write(1, "\b \b", 3);
        if (tmp_i != 0)
            password[--tmp_i] = 0;
    } else {
        !sgt->check ? write(1, "\b", 1) : 0;
        !sgt->check ? write(1, &sgt->c, 1) : 0;
        if (!sgt->check)
            password[tmp_i++] = sgt->c;
        sgt->check = 0;
    }
    sgt->i = tmp_i;
}

char *get_complete(char *password, shell_t *sh, sp_get_t *sgt)
{
    int tmp_i = sgt->i;
    if (sgt->c == '\t') {
        sgt->check = 1;
        printf("\r");
        special_output(sh);
        password[tmp_i] = '\0';
        password = autocompeltion(password);
        tmp_i = strlen(password);
        printf("%s", password);
        password[strlen(password)] = ' ';
    }
    sgt->i = tmp_i;
    return password;
}

static char *real_get(char **history, shell_t *sh)
{
    sp_get_t sgt = {0, 0, 0};
    int size_malloc = 128;
    history_t *hs = init_history(history);
    char *password = malloc(sizeof(char) * size_malloc);
    while ((sgt.c = getchar()) != '\n') {
        password = get_complete(password, sh, &sgt);
        sgt.check = check_arrows(hs, &password, sh, &sgt);
        super_getline_red(password , sh, &sgt);
        if (sgt.i >= (size_malloc) - 1) {
            size_malloc += 128;
            password = (char *)realloc(password, sizeof(char) * size_malloc);
        }
    }
    password[sgt.i] = '\0';
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
