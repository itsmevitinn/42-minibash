/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/24 01:13:39 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int numeric_argument(char *status);

void ft_exit(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;

	if (data->qty != 1)
	{
		data->pids[cmd->id] = fork();
		if (!data->pids[cmd->id])
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