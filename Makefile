NAME = minibash

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

PARSER = parser.c interpret_vars.c sub_arg.c cleanup.c interpret_redirects.c update_fd.c get_heredoc_input.c

EXEC = exec_bin.c exec_cmd.c exec_builtin.c

UTILS = parser_utils.c var_utils.c mem_utils.c utils.c data_utils.c bin_cmd_utils.c builtin_cmd_utils.c cd_utils.c main_utils.c env_utils.c

BUILT-IN = exit.c cd.c pwd.c echo.c env.c export.c unset.c

MAIN = minibash.c prompt.c fill_data.c precedence_analyzer.c

SIGNAL = signal.c

VARIABLES = var_lst.c cmd_lst.c environment.c

FUNCS = $(addprefix ./src/exec/, $(EXEC))			\
		$(addprefix ./src/main/, $(MAIN))			\
		$(addprefix ./src/signals/, $(SIGNAL))		\
		$(addprefix ./src/parser/, $(PARSER))		\
		$(addprefix ./src/builtin/, $(BUILT-IN))	\
		$(addprefix ./src/utils/, $(UTILS))	\
		$(addprefix ./src/variables/, $(VARIABLES))


RM = rm -rf

all:		$(NAME)

$(NAME):	$(FUNCS) $(LIBFT)
			@$(CC) $(FLAGS) $(FUNCS) $(LIBFT) -o $(NAME)
			@echo "\033[32m 💯 | minishell created. \033[0m"

$(LIBFT):
			$(MAKELIBFT)

clean:
			@${MAKE_IN_DIRECTORY} ${LIBFT_PATH} clean
			@${RM} ${NAME}.dSYM
			@echo "\033[33m 🧹 | minishell cleaned. \033[0m"

fclean: 	clean
			@${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean
			@$(RM) $(NAME)
			@echo "\033[33m 🌪️  | minishell all cleaned. \033[0m"

re:			fclean all

.PHONY:		all clean fclean re
