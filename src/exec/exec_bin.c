/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/09 15:05:02 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_fds(t_cmd_lst *cmd, t_cmd_info *data);
// static int	valid_absolute_path(t_cmd_lst *cmd);
static char	*find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst);
static void	run_absolute_path(t_cmd_lst *cmd, t_cmd_info *data,
				t_var_lst *env_lst);
static void	run_bin_path(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst,
				char *cmd_path);

void	exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	char	*cmd_path;

	if (!access(cmd->args[0], F_OK | X_OK))
		run_absolute_path(cmd, data, env_lst);
	else
	{
		cmd_path = find_bin_path(cmd, env_lst);
		if (!cmd_path)
		{
			command_not_found(cmd);
			cmd->not_found = 1;
		}
		else
			run_bin_path(cmd, data, env_lst, cmd_path);
	}
}

static void	run_absolute_path(t_cmd_lst *cmd, t_cmd_info *data,
		t_var_lst *env_lst)
{
	char	**env_matrix;

	env_matrix = list_to_matrix(env_lst);
	cmd->pid = fork();
	if (!cmd->pid)
	{
		setup_fds(cmd, data);
		execve(cmd->args[0], cmd->args, env_matrix);
	}
	free_matrix(env_matrix);
}

static void	run_bin_path(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst,
		char *cmd_path)
{
	char	**env_matrix;

	env_matrix = list_to_matrix(env_lst);
	cmd->pid = fork();
	if (!cmd->pid)
	{
		restore_sigint();
		setup_fds(cmd, data);
		execve(cmd_path, cmd->args, env_matrix);
	}
	free_matrix(env_matrix);
	free(cmd_path);
}

static char	*find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	char	**env_paths;
	char	*cmd_path;
	int		i;

	if (!*cmd->args[0] || !get_content("PATH", env_lst))
		return (NULL);
	i = 0;
	env_paths = ft_split(get_content("PATH", env_lst), ':');
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, cmd->args[0], 'f');
		if (!access(cmd_path, F_OK | X_OK))
		{
			free_matrix(env_paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_matrix(env_paths);
	return (NULL);
}

static void	setup_fds(t_cmd_lst *cmd, t_cmd_info *data)
{
	dup2(cmd->input, 0);
	dup2(cmd->output, 1);
	if (data->qty >= 2)
		close_all_pipes(data);
}
