/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** test for the minishell
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"

char **copy_double_tab(char **tab)
{
    int len = 0;
    char **copy;
    for (; tab[len] != NULL; ++len);
    copy = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; ++i)
        copy[i] = strdup(tab[i]);
    copy[len] = NULL;
    copy[0] = "PATH=/home/Cote2porc/.nvm/versions/node/v16.14.2/bin:"
    "/usr/local/bin:/usr/bin:/bin:/home/Cote2porc/bin:/usr"
    "/local/sbin:/usr/sbin:/var/lib/snapd/snap/bin";
    return copy;
}

extern char **environ;

Test(parsing, basic_test, .init=cr_redirect_stdout) {
    char *to_pars = "Hello world";
    char **parsed = parsing(to_pars);
    my_show_word_array(parsed);
    cr_assert_stdout_eq_str("Hello\nworld\n", "");
}

Test(cd, not_error, .init=cr_redirect_stdout) {
    char **test = malloc(sizeof(char *) * 3);
    int verif;
char **env = malloc(sizeof(char *) * 10);
    cd *cd_params = malloc(sizeof(cd) + 1);
    params_cd(cd_params);
    shell_t *sh = malloc(sizeof(shell_t));
    params_shell(0, NULL, sh);
    test[0] = "cd";
    test[1] = "tests";
    test[2] = NULL;
    verif = my_cd(test, sh, env);
    cr_assert_eq(0, verif);
}

Test(cd, not_error_2, .init=cr_redirect_stdout) {
    char **test = malloc(sizeof(char *) * 3);
    int verif;
    char **env = malloc(sizeof(char *) * 10);
    cd *cd_params = malloc(sizeof(cd) + 1);
    params_cd(cd_params);
    shell_t *sh = malloc(sizeof(shell_t));
    params_shell(0, NULL, sh);
    test[0] = "cd";
    test[1] = NULL;
    test[2] = NULL;
    verif = my_cd(test, sh, env);
    cr_assert_eq(0, verif);
}

Test(cd, not_error_3, .init=cr_redirect_stdout) {
char **test = malloc(sizeof(char *) * 3);
int i;
char **env = malloc(sizeof(char *) * 10);
env[0] = NULL;
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
path_to_home(sh->cd_params->modif_env[2]);
path_to_home(sh->cd_params->new_PWD[2]);
test[0] = "cd";
test[1] = "-";
test[2] = NULL;
i = my_cd(test, sh, env);
cr_assert_eq(0, i);
}

Test(cd, str_equal, .init=cr_redirect_stdout) {
int verif = is_str_equal("Hello", "Hellw");
cr_assert_eq(0, verif);
}

Test(env, set_env, .init=cr_redirect_stdout) {
    char **env = malloc(sizeof(char *) * 5);
    char **pars = malloc(sizeof(char *) * 5);
    shell_t *sh = malloc(sizeof(shell_t));
    params_shell(0, NULL, sh);
    int verif;
    env[0] = "VAR=value";
    env[1] = "THEO=pd";
    env[2] = "ALESSIO=bg";
    env[3] = NULL;
    pars[0] = "setenv";
    pars[1] = "OSCAR";
    pars[2] = "GIGABG";
    pars[3] = NULL;
    verif = set_env(env, pars, sh);
    cr_assert_eq(0, verif);
}

Test(env, unset_env, .init=cr_redirect_stdout) {
char **env = malloc(sizeof(char *) * 5);
char **pars = malloc(sizeof(char *) * 5);

int verif;
env[0] = "VAR=value";
env[1] = "THEO=pd";
env[2] = "ALESSIO=bg";
env[3] = NULL;
pars[0] = "unsetenv";
pars[1] = "THEO";
pars[2] = NULL;
verif = unset_env(env, "THEO");
cr_assert_eq(0, verif);
}

Test(env, unset_env_fail, .init=cr_redirect_stdout) {
char **env = malloc(sizeof(char *) * 5);
char **pars = malloc(sizeof(char *) * 5);
int verif;
env[0] = "VAR=value";
env[1] = "THEO=pd";
env[2] = "ALESSIO=bg";
env[3] = NULL;
pars[0] = "unsetenv";
pars[1] = "OSCAR";
pars[2] = NULL;
verif = unset_env(env, "OSCAR");
cr_assert_eq(1, verif);
}

Test(setenv, setenv_test, .init=cr_redirect_stdout) {
    char **test = malloc(sizeof(char *) * 5);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    test[0] = "setenv";
    test[1] = "VAR#";
    test[2] = "Value";
    test[3] = NULL;
cr_assert_eq(0, error_setenv(test, sh));
}

Test(setenv, setenv_test2, .init=cr_redirect_stdout) {
char **test = malloc(sizeof(char *) * 5);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
test[0] = "setenv";
test[1] = "#VAR";
test[2] = "Value";
test[3] = NULL;
cr_assert_eq(0, error_setenv(test, sh));
}

Test(setenv, setenv_test3, .init=cr_redirect_stdout) {
char **test = malloc(sizeof(char *) * 10);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
test[0] = "setenv";
test[1] = "VAR";
test[2] = "Value";
test[3] = "SAU";
test[4] = NULL;
cr_assert_eq(0, error_setenv(test, sh));
}

Test(setenv, setenv_test4, .init=cr_redirect_stdout) {
char **test = malloc(sizeof(char *) * 10);
test[0] = "setenv";
test[1] = "VAR";
test[2] = "Value";
test[3] = NULL;
cr_assert_str_neq("",set_value_two(test));
}
Test(commands_tools, verify_return, .init=cr_redirect_stdout){
(verify_return(0));
cr_assert_stdout_neq_str("Segmentation fault (core dumped)\n", "");
}

Test(commands_tools, my_put_str_er, .init=cr_redirect_stdout){
my_put_str_er("Segmentation fault (core dumped)\n");
cr_assert_stdout_neq_str("Segmentation fault (core dumped)\n", "");
}

Test(commands_tools, put_bin, .init=cr_redirect_stdout){
cr_assert_str_eq("/bin/ls", put_bin("ls"));
}
Test(commands_tools, semicolon, .init=cr_redirect_stdout){
    char **re = malloc(sizeof(char *) * 10);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    char *ui = "ls ; cd";
    re = semicolon(ui, sh, 0, 0);
    cr_assert_str_neq("ls", re[0]);
}

/*
Test(wrongcommand, not_error, .init=cr_redirect_stdout) {
char **test = malloc(sizeof(char *) * 3);
int verif;
char **env = malloc(sizeof(char *) * 10);
cd *cd_params = malloc(sizeof(cd) + 1);
params_cd(cd_params);
test[0] = "cd";
test[1] = "tests";
test[2] = NULL;
verif = process_commands("lq", test, cd_params);
cr_assert_eq(0, verif);
}
*/

Test(left_redirection, test, .init=cr_redirect_stdout)
{
    char **good = copy_double_tab(environ);
    char *command = strdup("cat < tests/test");
    cd *cd_params = malloc(sizeof(cd) + 1);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    params_cd(cd_params);
    process_commands(command, good, sh, false);
    cr_assert_stdout_eq_str("test", "");
}

Test(right_redirection, test, .init=cr_redirect_stdout)
{
    char **good = copy_double_tab(environ);
    char *command = strdup("echo ui > tests/tmp");
    char *check = strdup("cat tests/tmp");
    cd *cd_params = malloc(sizeof(cd) + 1);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    params_cd(cd_params);
    process_commands(command, good, sh, false);
    process_commands(check, good, sh, false);
    cr_assert_stdout_eq_str("ui\n", "");
}

Test(pipe, test, .init=cr_redirect_stdout)
{
    char **good = copy_double_tab(environ);
    char *command = strdup("cat tests/pipe_check | grep a | wc -m | cat -e");
    cd *cd_params = malloc(sizeof(cd) + 1);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    params_cd(cd_params);
    process_commands(command, good, sh, false);
    cr_assert_stdout_eq_str("8$\n", "");
}

Test(complex_command, test, .init=cr_redirect_stdout)
{
    char **good = copy_double_tab(environ);
    char *command = strdup("cat < tests/pipe_check | grep a | wc -m | cat -e > tests/complex");
    char *check = strdup("cat tests/complex");
    cd *cd_params = malloc(sizeof(cd) + 1);
shell_t *sh = malloc(sizeof(shell_t));
params_shell(0, NULL, sh);
    params_cd(cd_params);
    process_commands(command, good, sh, false);
    process_commands(check, good, sh, false);
    cr_assert_stdout_eq_str("8$\n", "");
}