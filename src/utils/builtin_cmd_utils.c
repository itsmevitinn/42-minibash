/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:46:28 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 18:45:47 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_cmd_info *data, t_var_lst **env_lst, int should_print)
{
	if (should_print)
		ft_putstr_fd("exit\n", 2);
	free(data->user_input);
	rl_clear_history();
	ft_varclear(env_lst);
	ft_cmdclear(&data->lst_cmd);
}

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
