NAME = minishell

MAKE_IN_DIRECTORY = make -C

# !!! need to run brew install radline  !!! #
FLAGS = -Wall -Wextra -g -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include #-Werror

MAKELIBFT = ${MAKE_IN_DIRECTORY} ./libft

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

CC = cc

EXEC = bin_cmd.c

MAIN = minishell.c

PROMPT = prompt.c

SIGNAL = signal.c

FUNCS = $(addprefix ./src/exec/, $(EXEC))		\
		$(addprefix ./src/main/, $(MAIN))	\
		$(addprefix ./src/prompt/, $(PROMPT))	\
		$(addprefix ./src/signals/, $(SIGNAL))	


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
