/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/05 10:20:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	numeric_argument(char *status);
static void	exec_exit(t_cmd_lst *cmd, t_cmd_info *data);

int	ft_exit(t_cmd_lst *cmd, t_cmd_info *data)
{
	if (!check_heredoc(cmd))
		return (0);
	if (data->qty > 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_exit(cmd, data);
		finish_fork_builtin(cmd);
	}
	else
		exec_exit(cmd, data);
	return (1);
}

static void	exec_exit(t_cmd_lst *cmd, t_cmd_info *data)
{
	int	new_status;

	if (!cmd->args[1])
	{
		if (data->qty == 1)
			printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (cmd->args[1] && numeric_argument(cmd->args[1]))
	{
		new_status = ft_atoi(cmd->args[1]);
		if (data->qty == 1)
			printf("exit\n");
		exit(new_status);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
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
