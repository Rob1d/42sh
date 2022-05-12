/*
** EPITECH PROJECT, 2022
** minshel
** File description:
** header fo the minshell
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <string.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <stdbool.h>
    #include <string.h>

typedef struct {
    char *old_cd;
    char *user;
    char *swap;
    char **modif_env;
    char **new_PWD;
} cd;

typedef struct shell_s {
    int last_return;
    int *separator_type;
    int len_separator;
    cd *cd_params;
}shell_t;

typedef struct {
    int len_pipe;
    char **env;
    char **commands;
    int pipe_fd[2];
    int return_last;
    shell_t *sh;
}pipe_t;

void no_acess(int file, char *n_file);
bool is_builtin_name(char *str);
bool is_builtin(pipe_t *ppt, int nb);
int process_commands(char *line, char **env, shell_t *sh, bool is_piped);
int pipe_gestion(char *command, char **env, shell_t *sh);
int left_redirection(char *command, char **env, shell_t *sh);
void suppr_command(char *command, char *launched, char c);
char *name_file(char *command, int i);
int right_redirection(char *command, char **env, shell_t *sh);
void check_execution(char **parsing_command, pipe_t *ppt);
void error_acess(char *pars);
void check_spaces(char **parsed);
char **split_commands(char *str);
void apply_old(char *old_cd, char *tmp_buf);
void params_cd(cd *cd_params);
int go_outside(char **parsed, cd *cd_params, char **env);
int go_home(char **parsed, cd *cd_params, char **env);
int minus_cd(cd *cd_params, char **env);
void my_put_str_er(char *str);
void verify_return(int rd);
char *put_bin(char *command);
char **wait_commands(shell_t *sh);
int path_to_home(char *cwd);
int search_in_env(char **env, char *set);
int unset_loop(char **env, char **pars);
int error_setenv(char **pars);
int is_letter(char c);
char *set_value_two(char **pars);
int is_env(char **env, char **pars);
int move_env(char **env, int i);
int len_env(char **env);
int my_cd(char **parsed, cd *cd_params, char **env);
int is_str_equal(char *str, char *to_test);
int launch_command(char **env, char **pars, shell_t *sh);
int verify_command(char **env, shell_t *sh);
char **parsing(char *str);
int str_len(char *str);
void my_putchar(char c);
int set_env(char **env, char **pars);
void my_show_word_array(char **tab);
int unset_env(char **env, char *to_reset);
char **parsing_path(char *str);
char *as_path(char **env, char *command);
char **semicolon(char *command, shell_t *sh, int i, int cp);
//my echo
bool my_echo(char **env, char *line, char **pars, shell_t *sh);
#endif
