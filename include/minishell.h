/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:30:44 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/05 11:27:48 by vsergio          ###   ########.fr       */
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

typedef struct	s_prompt
{
	char	*logname;
	char	*hostname;
	char	*current_dir;
	char	*display;
}				t_prompt;

typedef struct	s_var_list
{
	char				*name;
	void				*content;
	struct s_var_list	*next;
}				t_var_lst;

typedef struct	s_cmd_lst
{
	char				*filename;
	int					input;
	int					output;
	char				*delimiter;
	char				*line;
	char				**args;
	int					id;
	int					pid;
	struct s_cmd_lst	*next;
}				t_cmd_lst;

typedef struct	s_cmd_info
{
	int			qty;
	int			**pipes;
	t_cmd_lst	*lst_cmd;
}				t_cmd_info;

//MEM_UTILS FUNCTIONS
void		free_matrix(char **cmd_args);
void		free_pipes(t_cmd_info *data);

//UTILS FUNCTIONS
void		print_matrix(char **cmd_args);
void		close_all_pipes(t_cmd_info *data);

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

//EXEC_BUILTIN UTILS
int			try_echo_execution(t_cmd_lst *cmd);
int			try_cd_execution(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);
int			try_pwd_execution(t_cmd_lst *cmd);
int			try_export_execution(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);
int			try_unset_execution(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);
int			try_env_execution(t_cmd_lst *cmd, t_var_lst **env_lst);
int			try_exit_execution(t_cmd_lst *cmd, t_cmd_info *data);

//CD_UTILS FUNCTIONS
void		update_oldpwd(char *current_dir, t_var_lst *env);

//BIN_CMD_UTILS FUNCTIONS
int			finish_bin_cmd(t_cmd_lst *cmd);
void		command_not_found(t_cmd_lst *cmd);

//BUILTIN_CMD_UTILS FUNCTIONS
int			check_heredoc(t_cmd_lst *cmd);
int			execute_heredoc(t_cmd_lst *cmd);
void		finish_fork_builtin(t_cmd_lst *cmd);

//PARSER FUNCTIONS
t_cmd_lst	*parse_input(char *user_input, t_var_lst *env_lst);
int			check_syntax(char *cmd_line);
void		interpret_redirects(t_cmd_lst *lst_cmd, char *line);
void		interpret_vars(char **cmd, t_var_lst *env_lst);
void		cleanup(char **args);

//UTILS
void		remove_chunk(char *str, int len);
void		update_fd(t_cmd_lst *cmd, int type);
char		*skip_quote(char *cmd);
char		*sub_arg(char **arg, char *index, char *name, char *content);
int			is_builtin(char *cmd_name);
void		print_invalid_identifier(char *value, char *cmd);

//CLEANUP
void		remove_quotes(char *cmd);
char		*skip_variable(char *cmd);
char		*clean_quote(char *cmd);

//EXEC FUNCTIONS
void		exec_cmds(t_cmd_info *data, t_var_lst **env_lst);
int			exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst **env_lst);
int			exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
void		get_heredoc_input(t_cmd_lst *cmd);

//BULT-IN FUNCTIONS
int			cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
int			echo(t_cmd_lst *cmd);
int			pwd(t_cmd_lst *cmd);
int			env(t_cmd_lst *cmd, t_var_lst *env_lst);
int			export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);
int			unset(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst);
int			ft_exit(t_cmd_lst *cmd, t_cmd_info *data);

//SIGNAL_FUNCTIONS
void		setup_signals(void);
void		restore_sigint(void);

//VARIABlES FUNCTIONS
void		initialize_env(t_var_lst **lst);
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
