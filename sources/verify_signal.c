/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** gestion of the signals
*/

#include "../includes/minishell.h"

static void other_signal_check(int rd)
{
    if (WIFSTOPPED(rd)) {
        if (WSTOPSIG(rd) == SIGSEGV)
            my_put_str_er("Segmentation fault");
        if (WSTOPSIG(rd) == SIGFPE)
            my_put_str_er("Floating exception");
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
            my_put_str_er("Floating exception");
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