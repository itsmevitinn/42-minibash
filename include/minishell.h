/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:30:44 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/07 19:44:41 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_prompt
{
	char	*logname;
	char	*hostname;
	char	*current_dir;
	char	*display;
}				t_prompt;

typedef struct s_var_list
{
	char				*name;
	void				*content;
	struct s_var_list	*next;
}				t_var_lst;

typedef struct s_cmd_lst
{
	char				*in_file;
	char				*out_file;
	int					input;
	int					output;
	char				*delimiter;
	char				*line;
	char				**args;
	int					id;
	int					pid;
	struct s_cmd_lst	*next;
}				t_cmd_lst;

typedef struct s_cmd_info
{
	int			qty;
	int			**pipes;
	char		*user_input;
	t_cmd_lst	*lst_cmd;
	t_var_lst	*env_lst;
}				t_cmd_info;

//MEM_UTILS FUNCTIONS
void		free_matrix(char **cmd_args);
void		free_pipes(t_cmd_info *data);

//UTILS FUNCTIONS
void		print_matrix(char **cmd_args);
void		close_all_pipes(t_cmd_info *data);
void		run_commands(t_cmd_info *data);
void		get_exit_status(t_cmd_lst *lst_cmd, int cmd_qty);
void		free_resources(t_cmd_info *data);
void		handle_eof(t_var_lst **var_lst);
void		free_all(t_cmd_info *data, t_var_lst **env_lst, int should_print);

//PROMPT FUNCTIONS
char		*display_prompt(void);

//DATA_UTILS FUNCTIONS
int			cmds_quantity(t_cmd_info *data);

//FILL_DATA FUNCTIONS
void		fill_data(t_cmd_info *data);

//PRECEDENCE_ANALYZER FUNCTIONS
void		precedence_analyzer(t_cmd_info *data);
void		handle_cmd_pipes(t_cmd_lst *cmd, t_cmd_info *data);
void		handle_builtin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty);
void		handle_bin_cmd(t_cmd_lst *cmd, int **pipes, int cmd_qty);

//CD_UTILS FUNCTIONS
void		update_oldpwd(char *current_dir, t_var_lst *env);
void		no_such_file_or_directory(char *path, int cmd_qty, int *updater);
int			exec_new_path(char *path, int cmd_qty, t_var_lst *env_lst,
				int *updater);

//BIN_CMD_UTILS FUNCTIONS
int			finish_bin_cmd(t_cmd_lst *cmd);
void		command_not_found(t_cmd_lst *cmd);

//BUILTIN_CMD_UTILS FUNCTIONS
int			check_heredoc(t_cmd_lst *cmd);
int			execute_heredoc(t_cmd_lst *cmd);
void		finish_fork_builtin(t_cmd_lst *cmd);

//PARSER FUNCTIONS
int			parse_input(t_cmd_info *data);
int			check_syntax(char *cmd_line);
int			interpret_redirects(t_cmd_lst *lst_cmd, char *line);
void		interpret_vars(char **cmd, t_var_lst *env_lst);
void		cleanup(char **args);

//UTILS
int			update_fd(t_cmd_lst *cmd, int type);
int			whitespace_checker(char *input);
int			is_builtin(char *cmd_name);
int			has_syntax_error(int type, char *line, t_cmd_lst *cmd);
char		*skip_quote(char *cmd);
char		*sub_arg(char **arg, char *index, char *name, char *content);
void		print_invalid_identifier(char *value, char *cmd);
void		print_syntax_error(t_cmd_lst *cmd, char *str);
void		remove_chunk(char *str, int len);
int			count_args(char **args);

//CLEANUP
void		remove_quotes(char *cmd);
char		*skip_variable(char *cmd);
char		*clean_quote(char *cmd);

//EXEC FUNCTIONS
void		exec_cmds(t_cmd_info *data, t_var_lst **env_lst);
void		exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);
void		exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
void		get_heredoc_input(t_cmd_lst *cmd, int *here_pipe);

//BULT-IN FUNCTIONS
void		cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
void		echo(t_cmd_lst *cmd);
void		pwd(t_cmd_lst *cmd);
void		env(t_cmd_lst *cmd, t_var_lst *env_lst);
void		export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
void		unset(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst);
void		ft_exit(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);

//SIGNAL_FUNCTIONS
void		setup_signals(void);
void		restore_sigint(void);

//VARIABlES FUNCTIONS
void		initialize_env(t_cmd_info *data);
char		**split_env(char *str);

//ENVIRONMENT FUNCTIONS
void		free_env(void);

//VAR_LST FUNCTIONS
t_var_lst	*ft_var_new(char *name, void *content);
t_var_lst	*get_env(char *name, t_var_lst *variables);
void		ft_varadd_back(t_var_lst **head, t_var_lst *new);
void		ft_varclear(t_var_lst **head);
void		change_content(char *name, char *content, t_var_lst *variables);
char		*get_content(char *name, t_var_lst *env);
char		**list_to_matrix(t_var_lst *env_lst);
//LST_CMD FUNCTIONS
t_cmd_lst	*ft_cmd_new(char *cmd_line);
void		ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new);
void		ft_cmdclear(t_cmd_lst **head);

extern int	g_exit_status;

#endif
