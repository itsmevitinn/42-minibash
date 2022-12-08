#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct	s_prompt
{
	char *logname;
	char *hostname;
	char *current_dir;
	char *display;
}				t_prompt;

typedef struct	s_var_list
{
	char *name;
	char *content;
	struct s_var_list *next;
}				t_var_list;

//UTILS FUNCTIONS
void	free_matrix(char **splitted_cmd);

//PROMPT FUNCTIONS
char	*display_prompt(void);

//PARSER FUNCTIONS
void	parse_input(char *user_input, t_list *env_lst);

//EXEC FUNCTIONS
void	exec_bin_cmd(char *right_path, char **splitted_cmd);

//BULT-IN FUNCTIONS
int		isbuiltin(char **splitted_cmd, t_list *env_lst);
void	cd(char **splitted_cmd);
void	echo(char **splitted_cmd, int fd);
void	pwd(int fd);
void	env(t_list *env_lst, int fd);
void	ft_exit(char **splitted_cmd);

//SIGNAL_FUNCTIONS
void	setup_signals(void);

//VARIABlES FUNCTIONS
void	initialize_env(t_list **lst);

//ENVIRONMENT FUNCTIONS
void	free_env(void);

extern int exit_status;

#endif
