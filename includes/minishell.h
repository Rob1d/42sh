/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** header fo the 42sh
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
    #include <sys/stat.h>
    #define IS_LETTER(c) ((c >= 'A' && c <= 'Z') ||\
    (c >= 'a' && c <= 'z') && c != '_')
    #include <termios.h>

typedef struct echo_r_s {
    char *line;
    char start;
    int i;
}echo_r_t;

typedef struct if_params_s {
    char *params[2];
    char *equality_type;
    bool res;
    bool is_int;
    int params_int[2];
}if_params_t;

typedef struct backticks_s {
    int i;
    char *command;
    char *end_command;
}backticks_t;

typedef struct sp_get_s {
    int i;
    int c;
    int check;
}sp_get_t;

typedef struct history_s {
    int actual_history;
    char **history;
    int len;
}history_t;

typedef struct {
    char *old_cd;
    char *user;
    char *swap;
    char **modif_env;
    char **new_PWD;
} cd;

typedef struct var_s {
    char *name;
    char *value;
    struct var_s *next;
}var_t;

typedef struct shell_s {
    int last_return;
    int *separator_type;
    int len_separator;
    cd *cd_params;
    bool all_mode;
    char *user_name;
    var_t *lk_var;
}shell_t;

typedef struct {
    int len_pipe;
    char **env;
    char **commands;
    int pipe_fd[2];
    int return_last;
    shell_t *sh;
}pipe_t;

void params_shell(int av, char **argc, shell_t *sh);
int len_double_tab(char **tab);
bool str_start_with(char *str, char *start);
bool str_star_with_spe(char *str, char *str_start);
void display_alias(shell_t *sh);
char *extract_command_alias(char **alias, int i);
int len_spaces_alias(char *str, int i);
char **command_with_color(char **pars, shell_t *sh);
char *check_bactricks(char *command, char **env, shell_t *sh);
char *str_concat(char *first, char *sec);
bool set_alias(char **value, shell_t *sh, char *line);
char *read_last_line(char *line);
char *as_alias(char *command, shell_t *sh);
char **parsing_alias(char *str);
void write_to_rc(char *command, shell_t *sh);
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
int go_outside(char **parsed, shell_t *sh, char **env);
int go_home(char **parsed, shell_t *sh, char **env);
int minus_cd(shell_t *sh, char **env);
void my_put_str_er(char *str);
void verify_return(int rd);
char *put_bin(char *command);
char **wait_commands(shell_t *sh, char **env);
int path_to_home(char *cwd);
int search_in_env(char **env, char *set);
int unset_loop(char **env, char **pars);
int error_setenv(char **pars, shell_t *sh);
char *set_value_two(char **pars);
int is_env(char **env, char **pars, shell_t *sh);
int move_env(char **env, int i);
int len_env(char **env);
int my_cd(char **parsed, shell_t *sh, char **env);
int is_str_equal(char *str, char *to_test);
int launch_command(char **env, char **pars, shell_t *sh);
void verify_command(char **env, shell_t *sh);
char **parsing(char *str);
int str_len(char *str);
void my_putchar(char c);
int set_env(char **env, char **pars, shell_t *sh);
void my_show_word_array(char **tab);
int unset_env(char **env, char *to_reset);
char **parsing_path(char *str);
char *as_path(char **env, char *command);
char **semicolon(char *command, shell_t *sh, int i, int cp);
//my echo
bool my_echo(char **env, char *line, char **pars, shell_t *sh);
bool str_star_with(char *str, char *str_start);
//super_getline
char **received_input(shell_t *sh, bool reverse);
char *autocompeltion(char *inital_line);
char *super_getline(char **history, shell_t *sh);
void free_array(char **array);
void special_output(shell_t *sh);
int check_arrows(history_t *hs,
char **password, shell_t *sh, sp_get_t *sgt);

//check_if
int if_statement(char *command, char **env, shell_t *sh);

//var_interpreter
bool set_variable(char **pars, shell_t *sh);
void add_first_var(shell_t *sh);

//display_history
bool display_history(char *command, shell_t *sh);
char **my_db_copy(char *db[]);

//as_var
char *as_var(char *command, shell_t *sh, char **env);
#endif
