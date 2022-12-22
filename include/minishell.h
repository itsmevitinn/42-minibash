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

# define START 2
# define END 3

# define TRUNCATE 1
# define APPEND 2
# define INPUT 3
# define HEREDOC 4

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
	char *filename;
	int input;
	int output;
	int	has_truncate;
	char *heredoc_delimiter;
	char *line;
	char **args;
	int id;
	struct s_cmd_lst *next;
}				t_cmd_lst;

typedef struct	s_cmd_info
{
	int qty;
	int *pid;
	int **pipes;
	t_cmd_lst *lst_cmd;
}				t_cmd_info;

//UTILS FUNCTIONS
void	free_matrix(char **splitted_cmd);
void 	print_matrix(char **splitted_cmd);
int		whitespace_checker(char *input);

//PROMPT FUNCTIONS
char	*display_prompt(void);

//PARSER FUNCTIONS
t_cmd_lst	*parse_input(char *user_input, t_var_lst *env_lst);
int		check_syntax(char *cmd_line);
void	interpret_redirects(t_cmd_lst *lst_cmd, char *line);
void	interpret_vars(char **cmd, t_var_lst *env_lst);
void	cleanup(char **args);
/*--Utils--*/
void	remove_chunk(char *str, int len);
void	update_fd(t_cmd_lst *cmd, int type);
char	*skip_quote(char *cmd);
char	*sub_arg(char **arg, char *index, char *name, char *content);

//INTERPRET_VARS_UTILS

//EXEC FUNCTIONS
void	exec_bin_cmd(char *right_path, char **splitted_cmd);

//BULT-IN FUNCTIONS
int		is_builtin(t_cmd_lst *cmd, t_var_lst *env_lst);
void	cd(char **splitted_cmd, t_var_lst *env_lst);
void	echo(t_cmd_lst *cmd);
void	pwd(int fd);
void	env(t_var_lst *env_lst, int fd);
void	export(char **cmd, t_var_lst *env_lst, int fd);
void	unset(char **cmd, t_var_lst **env_lst, int fd);
void	ft_exit(char **splitted_cmd);

//BULT-IN UTILS
int	parse_cmd(char *cmd);

//DATA FUNCTIONS


//SIGNAL_FUNCTIONS
void	setup_signals(void);

//VARIABlES FUNCTIONS
void	initialize_env(t_var_lst **lst);
char	**split_env(char *str);

//ENVIRONMENT FUNCTIONS
void	free_env(void);

//VAR_LST FUNCTIONS
t_var_lst	*ft_var_new(char *name, void *content);
t_var_lst	*get_env(char *name, t_var_lst *variables);
void		ft_varadd_back(t_var_lst **head, t_var_lst *new);
void		ft_varclear(t_var_lst **head);
void		change_content(char *name, char *content, t_var_lst *variables);

extern int g_exit_status;

t_cmd_lst *ft_cmd_new(char *cmd_line);
void ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new);
#endif
