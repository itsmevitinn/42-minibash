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
	void *content;
	struct s_var_list *next;
}				t_var_lst;

typedef struct	s_cmd_lst
{
	char *env_name;
	char *infile;
	char *heredoc_delimiter;
	char *outfile;
	int	append;
	char *cmd_line;
	char **args;
	struct s_cmd_lst *next;
}				t_cmd_lst;

//UTILS FUNCTIONS
void	free_matrix(char **splitted_cmd);

//PROMPT FUNCTIONS
char	*display_prompt(void);

//PARSER FUNCTIONS
void	parse_input(char *user_input, t_var_lst *env_lst);

//EXEC FUNCTIONS
void	exec_bin_cmd(char *right_path, char **splitted_cmd);

//BULT-IN FUNCTIONS
int		is_builtin(char **splitted_cmd, t_var_lst *env_lst);
void	cd(char **splitted_cmd, t_var_lst *env_lst);
void	echo(char **splitted_cmd, int fd);
void	pwd(int fd);
void	env(t_var_lst *env_lst, int fd);
void	export(char **cmd, t_var_lst *env_lst, int fd);
void	ft_exit(char **splitted_cmd);

//SIGNAL_FUNCTIONS
void	setup_signals(void);

//VARIABlES FUNCTIONS
void	initialize_env(t_var_lst **lst);
char	**split_env(char *str);

//ENVIRONMENT FUNCTIONS
void	free_env(void);

//VAR_LST FUNCTIONS
t_var_lst	*ft_var_new(char *name, void *content);
void		ft_varadd_back(t_var_lst **head, t_var_lst *new);
void		ft_varclear(t_var_lst **head);
void		change_content(char *name, char *content, t_var_lst *variables);
int	is_env(char *name, t_var_lst *variables);

extern int exit_status;

t_cmd_lst *ft_cmd_new(char *cmd_line);
void ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new);
#endif
