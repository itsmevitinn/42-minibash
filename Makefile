NAME = minishell

MAKE_IN_DIRECTORY = make -C

# !!! need to run brew install radline  !!! #
uname_p := $(shell uname -p)

# !!! need to run brew install radline  !!! #
ifeq ($(uname_p), arm)
	FLAGS = -Wall -Wextra -Werror -g -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
else
	FLAGS = -Wall -Wextra -Werror -g -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
endif

MAKELIBFT = ${MAKE_IN_DIRECTORY} ./libft

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

CC = cc

PARSER = parser.c interpret_vars.c sub_arg.c cleanup.c utils.c syntax.c interpret_redirects.c update_fd.c

EXEC = bin_cmd.c get_heredoc_input.c

BUILT-IN = exit.c isbuiltin.c cd.c pwd.c echo.c env.c export.c unset.c

MAIN = minishell.c prompt.c

SIGNAL = signal.c

VARIABLES = environment.c var_lst.c split_env.c

FUNCS = $(addprefix ./src/exec/, $(EXEC))			\
		$(addprefix ./src/main/, $(MAIN))			\
		$(addprefix ./src/signals/, $(SIGNAL))		\
		$(addprefix ./src/parser/, $(PARSER))		\
		$(addprefix ./src/builtin/, $(BUILT-IN))	\
		$(addprefix ./src/variables/, $(VARIABLES))


RM = rm -rf

all:		$(NAME)

$(NAME):	$(FUNCS) $(LIBFT)
			@$(CC) $(FLAGS) $(FUNCS) $(LIBFT) -o $(NAME)
			@echo "\033[32m 💯 | minishell created."

$(LIBFT): 
			$(MAKELIBFT)

clean: 
			@${RM} ${NAME}.dSYM
			@echo "\033[33m 🧹 | minishell cleaned."

fclean: 	clean
			@${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean
			@$(RM) $(NAME)
			@echo "\033[33m 🌪️  | minishell all cleaned."

re:			fclean all

.PHONY:		all clean fclean re
