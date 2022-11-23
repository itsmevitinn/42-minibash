/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:26:12 by vsergio           #+#    #+#             */
/*   Updated: 2022/08/30 12:05:01 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_list_gnl
{
	char				*string;
	struct s_list_gnl	*next;
}						t_list_gnl;

typedef struct s_doubly_list
{
	void					*string;
	struct s_doubly_list	*next;
	struct s_doubly_list	*previous;
}							t_doubly_list;

int			ft_isalpha(int c);
int			ft_isdigit(int a);
int			ft_isalnum(int a);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_atoi(const char *str);
char		*ft_strdup(char *s1);
int			ft_toupper(int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list_gnl	*ft_lstlast_gnl(t_list_gnl *lst);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*get_next_line(int fd);
char		*get_next_line_bonus(int fd);
void		read_and_stash(t_list_gnl **stash, int fd);
void		add_to_stash(t_list_gnl **stash, char *buffer, int readed);
void		extract_line(t_list_gnl *stash, char **line);
void		clean_stash(t_list_gnl **stash);
int			found_newline(t_list_gnl *stash);
void		generate_line(t_list_gnl *stash, char **list);
void		free_stash(t_list_gnl *stash);
int			ft_printf(const char *string, ...);
char		*ft_utoa(unsigned int n);
char		*ft_ultohex(unsigned long address, char *hexbase);
int			ft_putchar_int(char c);
int			ft_putstr_int(char *s);
int			size_and_print_uint(va_list list_arg, char check);
int			size_and_print_int(va_list list_arg);
int			size_and_print_hex(va_list list_arg, char *basehex, char check);
#endif
