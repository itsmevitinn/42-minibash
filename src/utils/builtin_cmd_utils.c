/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:46:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/27 20:37:51 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_heredoc(t_cmd_lst *cmd)
{
	if (cmd->delimiter)
		if (!execute_heredoc(cmd))
			return (0);
	return (1);
}

int execute_heredoc(t_cmd_lst *cmd)
{
	int status;
	int heredoc_pid;

	heredoc_pid = fork();
	if (!heredoc_pid)
	{
		restore_sigint();
		get_heredoc_input(cmd);
		exit(0);
	}
	waitpid(heredoc_pid, &status, 0);
	if (!WIFEXITED(status))
		return (0);
	else
		return (1);
}
