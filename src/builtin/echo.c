/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/04 11:30:29 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	has_option(char *arg);

int	echo(t_cmd_lst *cmd)
{
	int	content_index;
	int	trailing_newline;

	if (!check_heredoc(cmd))
		return (0);
	cmd->pid = fork();
	if (!cmd->pid)
	{
		content_index = -1;
		trailing_newline = 1;
		if (!cmd->args[1])
		{
			ft_putstr_fd("\n", cmd->output);
			exit(0);
		}
		else if (has_option(cmd->args[1]))
		{
			content_index = 2;
			trailing_newline = 0;
		}
		else
			content_index = 1;
		while (cmd->args[content_index])
		{
			ft_putstr_fd(cmd->args[content_index], cmd->output);
			if (cmd->args[content_index + 1])
				write(cmd->output, " ", 1);
			content_index++;
		}
		if (trailing_newline)
			write(cmd->output, "\n", 1);
		exit(0);
	}
	finish_fork_builtin(cmd);
	return (1);
}

static int	has_option(char *arg)
{
	if (!ft_strncmp(arg, "-n", 2) && ft_strlen(arg) == 2)
		return (1);
	return (0);
}
