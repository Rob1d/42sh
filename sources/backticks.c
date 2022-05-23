/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** backticks gestion
*/

#include "../includes/minishell.h"

static void read_command(backticks_t *bck)
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

static int change_backtricks(backticks_t *bck, char **env, shell_t *sh)
{
    char **pars;
    char *tmp_command = strdup(bck->command);
    int j = 0;
    int fd = open(".tmp_file", O_CREAT | O_WRONLY, 0664);
    int pid = 0;
    int rd = 0;
    bck->command[bck->i++] = ' ';tmp_command += bck->i;
    for (; bck->command[bck->i] != '`' && bck->command[bck->i] != '\0'; ++bck->i)
        bck->command[bck->i] = ' ';
    bck->command[bck->i] = '\0';
    for (; tmp_command[j] != '`' && tmp_command[j] != '\0'; ++j);
    tmp_command[j] = '\0';pars = parsing(tmp_command);pid = fork();
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);launch_command(env, pars, sh);exit(0);
    }
    waitpid(pid, &rd, 0);close(fd);return bck->i;
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
            read_command(&bck);
        }
    return bck.command;
}