/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/24 17:52:52 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int numeric_argument(char *status);

void ft_exit(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;

	if (cmd->delimiter)
	{
		if (!fork())
		{
			restore_sigint();
			get_heredoc_input(cmd);
			exit(0);
		}
		wait(&status);
		if (!WIFEXITED(status))
			return;
	}
	if (data->qty != 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
		{
			if (!cmd->args[1])
				exit(EXIT_SUCCESS);
			else if (cmd->args[1] && numeric_argument(cmd->args[1]))
			{
				status = ft_atoi(cmd->args[1]);
				exit(status);
			}
			else
			{
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(cmd->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
		}
	}
	else
	{
		if (!cmd->args[1])
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (cmd->args[1] && numeric_argument(cmd->args[1]))
		{
			status = ft_atoi(cmd->args[1]);
			printf("exit\n");
			exit(status);
		}
		else
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

static int numeric_argument(char *status)
{
	while (*status)
	{
		if (*status >= '0' && *status <= '9')
			status++;
		else
			return (0);
	}
	return (1);
}