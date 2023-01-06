/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:46:28 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 16:40:44 by vsergio          ###   ########.fr       */
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
	int	here_pipe[2];

	pipe(here_pipe);
	cmd->input = here_pipe[0];
	heredoc_pid = fork();
	if (!heredoc_pid)
	{
		restore_sigint();
		get_heredoc_input(cmd, here_pipe);
		exit(0);
	}
	close(here_pipe[1]);
	waitpid(heredoc_pid, &status, 0);
	if (!WIFEXITED(status))
	{
		g_exit_status = 1;
		return (0);
	}
	else
		return (1);
}

void	finish_fork_builtin(t_cmd_lst *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}
