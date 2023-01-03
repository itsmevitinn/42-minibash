/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/03 17:17:15 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_fds(t_cmd_lst *cmd, t_cmd_info *data);
static void	try_absolute_path(t_cmd_lst *cmd, t_var_lst *env_lst);
static void	find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst);

int	exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	cmd->pid = fork();
	if (!cmd->pid)
	{
		restore_sigint();
		if (cmd->delimiter)
			get_heredoc_input(cmd);
		setup_fds(cmd, data);
		try_absolute_path(cmd, env_lst);
		find_bin_path(cmd, env_lst);
		command_not_found(cmd);
	}
	if (!finish_bin_cmd(cmd))
		return (0);
	return (1);
}

static void	setup_fds(t_cmd_lst *cmd, t_cmd_info *data)
{
	dup2(cmd->input, 0);
	dup2(cmd->output, 1);
	if (data->qty >= 2)
		close_all_pipes(data);
}

static void	find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	char	**env_paths;
	char	**env_matrix;
	char	*cmd_path;
	int		i;

	i = 0;
	env_paths = ft_split(get_content("PATH", env_lst), ':');
	env_matrix = list_to_matrix(env_lst);
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, cmd->args[0], 'f');
		if (!access(cmd_path, F_OK | X_OK))
			execve(cmd_path, cmd->args, env_matrix);
		// freeing wrong path
		free(cmd_path);
		i++;
	}
	free_matrix(env_matrix);
	free_matrix(env_paths);
}

static void	try_absolute_path(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	char **env_matrix;

	env_matrix = list_to_matrix(env_lst);
	if (!access(cmd->args[0], F_OK | X_OK))
		execve(cmd->args[0], cmd->args, env_matrix);
	free_matrix(env_matrix);
}
