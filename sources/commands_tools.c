/*
** EPITECH PROJECT, 2022
** minishell
** File description:
** tools for the commands
*/

#include "../includes/minishell.h"

void read_command(backticks_t *bck)
{
    int fd = open(".tmp_file", O_RDONLY);
    struct stat st;
    char *buf = NULL;
    size_t len = 0;
    stat(".tmp_file", &st);
    buf = malloc(sizeof(char) * st.st_size + 1);
    len = read(fd, buf, st.st_size);
    buf[len] = '\0';
    remove(".tmp_file");
    for (int j = 0; buf[j] != '\0'; ++j)
        if (buf[j] == '\n')
            buf[j] = ' ';
    bck->command[strlen(bck->command) - 1] = '\0';
    bck->command = realloc(bck->command,
    sizeof(char) * (strlen(bck->command) * strlen(buf)) + 2);
    sprintf(bck->command, "%s%s%s", bck->command, buf, bck->end_command);
}

int change_backtricks(backticks_t *bck, char **env, shell_t *sh)
{
    char **pars;
    char *tmp_command = strdup(bck->command);
    int j = 0;
    int fd = open(".tmp_file", O_CREAT | O_WRONLY, 0664);
    int pid = 0;
    int rd = 0;
    bck->command[bck->i++] = ' ';
    tmp_command += bck->i;
    for (; bck->command[bck->i] != '`' && bck->command[bck->i] != '\0'; ++bck->i)
        bck->command[bck->i] = ' ';
    bck->command[bck->i] = '\0';
    printf("%s\n", bck->command);
    for (; tmp_command[j] != '`' && tmp_command[j] != '\0'; ++j);
    tmp_command[j] = '\0';
    pars = parsing(tmp_command);
    pid = fork();
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        launch_command(env, pars, sh);
        exit(0);
    }
    waitpid(pid, &rd, 0);
    close(fd);
    return bck->i;
}

char *check_bactricks(char *command, char **env, shell_t *sh)
{
    backticks_t bck;
    int i = 0;
    bck.i = 0;
    bck.command = strdup(command);
    for (; command[i] != '\0'; ++i)
        if (command[i] == '`') {
            bck.i = i;
            bck.end_command = strdup(bck.command);
            i = change_backtricks(&bck, env, sh);
            bck.end_command += i + 1;
            printf("end_comm = %s i = %d\n", bck.end_command, i);
            read_command(&bck);
        }
    return bck.command;
}

char **wait_commands(shell_t *sh, char **env)
{
    char *buf = NULL;
    char **re;
    size_t line_size = 0;
    char **history = received_input(sh);
    sh->all_mode ? special_output(sh) : printf("42sh > ");
    if (history != NULL && sh->all_mode) {
        buf = super_getline(history, sh);
        line_size = strlen(buf);
    } else {
        line_size = getline(&buf, &line_size, stdin);
        if (line_size == -1)
            exit(0);
        buf[line_size - 1] = '\0';
    }
    if (line_size == 1)
        buf = "ui";
    write_to_rc(buf, sh);
    buf = check_bactricks(buf, env, sh);
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
