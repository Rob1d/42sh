##
## EPITECH PROJECT, 2022
## minishell1
## File description:
## makefile for minshell
##

SRC	=	sources/main.c	\
		sources/commands.c	\
		sources/my_cd.c	\
		sources/parsing.c	\
		sources/env_gestion.c	\
		sources/shell_tools.c	\
		sources/error_setenv.c	\
		sources/unsetenv.c	\
		sources/commands_tools.c	\
		sources/my_cd_tools.c	\
		sources/pipe_gestion.c	\
		sources/split_commands.c	\
		sources/split_commands_tools.c	\
		sources/right_redirection.c	\
		sources/left_redirection.c	\
		sources/check_good_env.c	\
		sources/pars_path.c	\
		sources/semicolon.c	\
		sources/builtins_tools.c

SRC_T =	sources/commands.c	\
        sources/my_cd.c	\
        sources/parsing.c	\
        sources/env_gestion.c	\
		sources/shell_tools.c	\
		sources/error_setenv.c	\
		sources/unsetenv.c	\
		sources/commands_tools.c	\
		sources/my_cd_tools.c	\
		sources/pipe_gestion.c	\
		sources/split_commands.c	\
		sources/split_commands_tools.c	\
		sources/right_redirection.c	\
		sources/left_redirection.c	\
		sources/check_good_env.c	\
		sources/pars_path.c	\
		sources/semicolon.c	\
		sources/builtins_tools.c



LIB =  -O2 -Wall

NAME	=	mysh

OBJ	=	$(SRC:.c=.o)

all: ${NAME}

$(NAME): $(OBJ)
	gcc $(LIB) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f unit_tests*

fclean:	clean
	rm -f $(NAME)

git: fclean
	git add *
	git commit -m "$m"
	git push

tests_run : fclean
	gcc -o unit_tests $(SRC_T) tests/test_shell.c --coverage -lcriterion
	./unit_tests

re:	fclean all