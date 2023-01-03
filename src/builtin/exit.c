/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/02 21:27:02 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	numeric_argument(char *status);

int	ft_exit(t_cmd_lst *cmd, t_cmd_info *data)
{
	int	status;

	if (!check_heredoc(cmd))
		return (0);
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
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	return (1);
}

static int	numeric_argument(char *status)
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
