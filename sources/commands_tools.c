/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** tools for the commands
*/

#include "../includes/minishell.h"

char **wait_commands(shell_t *sh)
{
    char *buf = NULL;
    char **re;
    size_t line_size = 0;
    write(1, "Rob1 > ", 7);
    line_size = getline(&buf, &line_size, stdin);
    if (line_size == -1)
        exit(0);
    buf[line_size - 1] = '\0';
    if (line_size == 1)
        buf = "ui";
    re = semicolon(buf, sh, 0, 0);
    return re;
}

char *put_bin(char *command)
{
    char *full_command = malloc(sizeof(char) * str_len(command) + 6);
    char *bin = "/bin/";
    for (int i = 0; i < 5; ++i)
        full_command[i] = bin[i];
    for (int i = 0; command[i] != '\0'; ++i)
        full_command[i + 5] = command[i];
    return full_command;
}

void my_put_str_er(char *str)
{
    write(2, str, str_len(str));
}

static void other_signal_check(int rd)
{
    if (WIFSTOPPED(rd)) {
        if (WSTOPSIG(rd) == SIGSEGV)
            my_put_str_er("Segmentation fault");
        if (WSTOPSIG(rd) == SIGFPE)
            my_put_str_er("Floating point exception");
        if (WSTOPSIG(rd) == SIGILL)
            my_put_str_er("Illegal instruction");
        if (WSTOPSIG(rd) == SIGABRT)
            my_put_str_er("Abort");
        if (WSTOPSIG(rd) == SIGTRAP)
            my_put_str_er("Trace/breakpoint trap");
        if (WSTOPSIG(rd) == SIGBUS)
            my_put_str_er("Bus error");
        write(2, "\n", 1);
    }
}

void verify_return(int rd)
{
    if (WIFSIGNALED(rd)) {
        if (WTERMSIG(rd) == SIGSEGV)
            my_put_str_er("Segmentation fault");
        if (WTERMSIG(rd) == SIGFPE)
            my_put_str_er("Floating point exception");
        if (WTERMSIG(rd) == SIGILL)
            my_put_str_er("Illegal instruction");
        if (WTERMSIG(rd) == SIGABRT)
            my_put_str_er("Abort");
        if (WTERMSIG(rd) == SIGTRAP)
            my_put_str_er("Trace/breakpoint trap");
        if (WTERMSIG(rd) == SIGBUS)
            my_put_str_er("Bus error");
        if (WCOREDUMP(rd))
            my_put_str_er(" (core dumped)");
        write(2, "\n", 1);
    }
    other_signal_check(rd);
}
