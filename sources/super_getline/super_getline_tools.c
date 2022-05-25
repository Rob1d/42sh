/*
** EPITECH PROJECT, 2022
** super_getline tools
** File description:
** getline 42sh
*/

#include "../../includes/minishell.h"

static void history_up(history_t *hs,
char **password, shell_t *sh, sp_get_t *sgt)
{
    if (sgt->c == 'A' && hs->actual_history < hs->len - 1) {
        for (int w = 0; w < sgt->i; ++w)
            write(1, "\b \b", 3);
        write(1, "\r", 1);
        special_output(sh);
        sgt->i = 0;
        ++hs->actual_history;
        printf("%s", hs->history[hs->actual_history]);
        sgt->i = strlen(hs->history[hs->actual_history]);
        *password = strdup(hs->history[hs->actual_history]);
        *password = realloc(*password, 128);
    }
}

static void history_down(history_t *hs,
char **password, shell_t *sh, sp_get_t *sgt)
{
    if (sgt->c == 'B' && hs->actual_history > 0) {
        for (int w = 0; w < sgt->i; ++w)
            write(1, "\b \b", 3);
        write(1, "\r", 1);
        special_output(sh);
        sgt->i = 0;
        --hs->actual_history;
        printf("%s", hs->history[hs->actual_history]);
        sgt->i = strlen(hs->history[hs->actual_history]);
        *password = strdup(hs->history[hs->actual_history]);
        *password = realloc(*password, 128);
    }
}

int check_arrows(history_t *hs,
char **password, shell_t *sh, sp_get_t *sgt)
{
    int tmp_i = sgt->i;
    if (sgt->c == 27) {
        sgt->c = getchar();
        sgt->c = getchar();
        for (int w = 0; w < 4; ++w)
            write(1, "\b \b", 3);
        history_up(hs, password, sh, sgt);
        history_down(hs, password, sh, sgt);
        if (sgt->c == 'D' && sgt->i > 0) {
            write(1, "\b\b", 2);
            write(1, &password[tmp_i], 1);
        }
        if (sgt->c == 'C')
            write(1, &password[tmp_i - 1], 1);
        return 1;
    }
    return 0;
}
