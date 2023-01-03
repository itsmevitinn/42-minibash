/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:46:28 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/02 21:19:18 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_heredoc(t_cmd_lst *cmd)
{
	if (cmd->delimiter)
	{
		if (!execute_heredoc(cmd))
			return (0);
	}
	return (1);
}

int	execute_heredoc(t_cmd_lst *cmd)
{
	int	status;
	int	heredoc_pid;

	heredoc_pid = fork();
	if (!heredoc_pid)
	{
		restore_sigint();
		get_heredoc_input(cmd);
		exit(0);
	}
	waitpid(heredoc_pid, &status, 0);
	if (!WIFEXITED(status))
	{
		g_exit_status = 1;
		return (0);
	}
	else
		return (1);
}

void	finish_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data)
{
	int	status;

	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}
