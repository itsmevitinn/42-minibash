SRCS	= ft_isspace.c ft_split_quotes.c ft_strtrim_edges.c ft_atoi_push.c ft_printf.c ft_printf_free.c ft_putchar_int.c ft_putstr_int.c ft_ultohex.c ft_utoa.c get_next_line.c get_next_line_utils.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_atoi.c ft_strdup.c ft_toupper.c ft_strlcat.c ft_strlcpy.c ft_strrchr.c ft_strchr.c ft_tolower.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_strncmp.c ft_strnstr.c ft_itoa.c ft_putendl_fd.c ft_striteri.c ft_strmapi.c ft_putnbr_fd.c ft_split.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

AR_RC 	= ar rc

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@${AR_RC} ${NAME} ${OBJS}
			@echo "\033[32m 💯 | Libft created."

bonus:		${OBJS_BONUS}
			@${AR_RC} ${NAME} ${OBJS_BONUS}
			@echo "\033[32m ✨ | Bonus libft created."

all:		$(NAME)

clean:		
			@${RM} ${OBJS}
			@${RM} ${OBJS_BONUS}
			@echo "\033[33m 🧹 | Libft cleaned."

fclean:		clean
			@${RM} ${NAME}
			@echo "\033[33m 🌪️  | Libft all cleaned."

re:		fclean all

.PHONY:		all clean fclean re
