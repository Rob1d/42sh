#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct history_s {
    int actual_history;
    char **history;
    int len;
}history_t;

int check_arrows(history_t *hs, int c, int *i, char **password)
{
    if (c == 27) {
        c = getchar();
        c = getchar();
        for (int w = 0; w < 4; ++w) {
            write(1, "\b", 1);
            write(1, " ", 1);
            write(1, "\b", 1);
        }
        if (c == 'A' && hs->actual_history < hs->len - 1) {
            for (int w = 0; w < *i; ++w) {
                write(1, "\b", 1);
                write(1, " ", 1);
                write(1, "\b", 1);
            }
            *i = 0;
            ++hs->actual_history;
            write(1, hs->history[hs->actual_history], strlen(hs->history[hs->actual_history]));
            *i = strlen(hs->history[hs->actual_history]);
            *password = strdup(hs->history[hs->actual_history]);
            *password = realloc(*password, 128);
        }
        if (c == 'B' && hs->actual_history > 0) {
            for (int w = 0; w < *i; ++w) {
                write(1, "\b", 1);
                write(1, " ", 1);
                write(1, "\b", 1);
            }
            *i = 0;
            --hs->actual_history;
            write(1, hs->history[hs->actual_history], strlen(hs->history[hs->actual_history]));
            *i = strlen(hs->history[hs->actual_history]);
            *password = strdup(hs->history[hs->actual_history]);
            *password = realloc(*password, 128);
        }
        if (c == 'D') {
            write(1, "\b\b", 2);
            write(1, &password[*i - 1], 1);
        }
        if (c == 'C')
            write(1, &password[*i - 1], 1);
        return 1;
    }
    return 0;
}

history_t *init_history(char **history)
{
    int i = 0;
    history_t *hs = malloc(sizeof(history_t));
    for (; history[i] != NULL; ++i);
    hs->len = i;
    hs->history = history;
    hs->actual_history = -1;
    return hs;
}

void super_getline_red(char c, int *i, char *password, int *check)
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

char *real_get(char **history)
{
    int c = 0;
    int i = 0;
    int check = 0;
    int size_malloc = 128;
    history_t *hs = init_history(history);
    char *password = malloc(sizeof(char) * size_malloc);
    while((c = getchar()) != '\n') {
        check = check_arrows(hs, c, &i, &password);
        super_getline_red(c, &i, password, &check);
        if (i >= (size_malloc) - 1) {
            size_malloc += 128;
            password = (char *)realloc(password, sizeof(char) * size_malloc);
        }
    }
    password[i] = '\0';
    for (int x = 0; hs->history[x] != NULL; ++x)
        free(hs->history[x]);
    free(hs->history);
    free(hs);
    return password;
}

char *super_getline(char **history)
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
    printf("Rob1 > ");
    ret = real_get(history);
    if (tcsetattr( STDIN_FILENO, TCSANOW, &oldt) != 0) {
        perror("tcsetattr");
        return (NULL);
    }
    return ret;
}

int main(void)
{
    char **history;
    history = malloc(sizeof(char *) * 4);
    history[0] = strdup("ls");
    history[1] = strdup("cd");
    history[2] = strdup("echo lol");
    history[3] = NULL;
    char *get = super_getline(history);
    printf("%s\n", get);
    free(get);
    return 0;
}
