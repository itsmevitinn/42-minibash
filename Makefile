NAME = minishell

FLAGS = -Wall -Wextra -Werror -g -lreadline

CC = cc

SRC_DIR = ./src/

SRCS = minishell.c

FUNCS = $(addprefix $(SRC_DIR), $(SRCS))

RM = rm -rf

all:		$(NAME)

$(NAME):	$(FUNCS)
			@$(CC) $(FLAGS) $(FUNCS) -o $(NAME)
			@echo "\033[32m 💯 | minishell created."

clean: 
			@${RM} ${NAME}.dSYM
			@echo "\033[33m 🧹 | minishell cleaned."

fclean: 	clean
			@$(RM) $(NAME)
			@echo "\033[33m 🌪️  | minishell all cleaned."

re:			fclean all

.PHONY:		all clean fclean re
