##
## EPITECH PROJECT, 2022
## 42sh
## File description:
## makefile for 42sh
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
		sources/builtins_tools.c	\
		sources/my_echo.c	\
		sources/myshrc_gestion.c	\
		sources/pars_alias.c	\
		sources/super_getline/super_getline.c	\
		sources/super_getline/get_history.c	\
		sources/super_getline/output_line.c		\
		sources/super_getline/completion.c	\
		sources/backticks.c


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
		sources/builtins_tools.c	\
		sources/my_echo.c	\
		sources/myshrc_gestion.c	\
		sources/pars_alias.c	\
		sources/super_getline/super_getline.c	\
		sources/super_getline/get_history.c	\
		sources/super_getline/output_line.c		\
		sources/super_getline/completion.c	\
		sources/backticks.c



LIB =  -O2 -Wall

NAME	=	42sh

OBJ	=	$(SRC:.c=.o)

CFLAGS += -g

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
