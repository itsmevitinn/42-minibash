/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/30 01:43:14 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void setup_fds(t_cmd_lst *cmd, t_cmd_info *data);
static void try_absolute_path(t_cmd_lst *cmd);
static void find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst);

int exec_bin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{

	cmd->pid = fork();
	if (!cmd->pid)
	{
		restore_sigint();
		if (cmd->delimiter)
			get_heredoc_input(cmd);
		setup_fds(cmd, data);
		try_absolute_path(cmd);
		find_bin_path(cmd, env_lst);
		command_not_found(cmd);
	}
	if (!finish_bin_cmd(cmd))
		return (0);
	return (1);
}

static void setup_fds(t_cmd_lst *cmd, t_cmd_info *data)
{
	dup2(cmd->input, 0);
	dup2(cmd->output, 1);
	if (data->qty >= 2)
		close_all_pipes(data);
}

static void find_bin_path(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	char **paths;
	char *full_path;
	char *temp;
	int i;

	i = 0;
	paths = ft_split(get_content("PATH", env_lst), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/", 0);
		full_path = ft_strjoin(temp, cmd->args[0], 1);
		if (!access(full_path, F_OK | X_OK))
			execve(full_path, cmd->args, NULL);
		// free wrong path
		free(full_path);
		i++;
	}
	free_matrix(paths);
}

static void try_absolute_path(t_cmd_lst *cmd)
{
	if (!access(cmd->args[0], F_OK | X_OK))
		execve(cmd->args[0], cmd->args, NULL);
}
